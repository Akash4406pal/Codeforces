/**
 * organize.js
 * 
 * Automatically organizes .cpp problem files located at the repository root into
 * their appropriate topic folders using metadata from the .cph directory.
 * If the topic folder doesn't exist yet, it creates it automatically.
 * 
 * It also:
 * 1. Updates CPH test case metadata (.prob file srcPath & hash-based filename).
 * 2. Updates the Problem Catalog and statistics in README.md.
 */

const fs = require('fs');
const path = require('path');
const crypto = require('crypto');
const { updateReadme } = require('./update-readme');

const ROOT_DIR = path.resolve(__dirname, '..');
const CPH_DIR = path.join(ROOT_DIR, '.cph');
const README_PATH = path.join(ROOT_DIR, 'README.md');

// Directories to ignore when searching for or organizing files
const IGNORED_DIRS = new Set([
  '.git',
  '.github',
  '.cph',
  '.vscode',
  '.idea',
  'scripts',
  'node_modules'
]);

// Known topic aliases to maintain consistency with existing structure
const TOPIC_ALIASES = {
  'prefix sums': 'Prefixes',
  'prefix sums and contribution': 'Prefixes',
  'prefixes': 'Prefixes',
  'warmup contest': 'Safari',
  'safari': 'Safari',
  'two pointers': 'Sliding Window and Two Pointers',
  'sliding window': 'Sliding Window and Two Pointers',
  'sliding window and two pointers': 'Sliding Window and Two Pointers',
  'time and space complexity': 'Time and Space Complexity',
  'sets and maps': 'Sets and Maps',
  'linked list': 'Linked List',
  'binary search': 'Binary Search',
  'backtracking': 'Backtracking',
  'intro to c++': 'Introduction to C++',
  'introduction to c++': 'Introduction to C++',
  'arrays': 'Arrays'
};

/**
 * Normalizes absolute path for CPH (Competitive Programming Helper) MD5 hashing.
 * CPH on Windows uses lowercase drive letters (e.g. c:\...) and backslashes.
 */
function getCphPath(absPath) {
  let p = path.normalize(absPath);
  if (p.length > 1 && p[1] === ':') {
    p = p[0].toLowerCase() + p.slice(1);
  }
  return p;
}

/**
 * Generates MD5 hash for CPH problem files based on the normalized file path.
 */
function getCphHash(cphPath) {
  return crypto.createHash('md5').update(cphPath).digest('hex');
}

/**
 * Safely reads and parses a JSON file that may contain a UTF-8 BOM.
 */
function readJsonSafe(filePath) {
  try {
    let content = fs.readFileSync(filePath, 'utf8');
    if (content.charCodeAt(0) === 0xfeff) {
      content = content.slice(1);
    }
    return JSON.parse(content);
  } catch (err) {
    return null;
  }
}

/**
 * Scans .cph folder to learn existing group-to-folder and contest-to-folder mappings.
 */
function learnExistingMappings() {
  const groupToFolder = new Map();
  const contestToFolder = new Map();

  if (!fs.existsSync(CPH_DIR)) return { groupToFolder, contestToFolder };

  const entries = fs.readdirSync(CPH_DIR);
  for (const entry of entries) {
    if (!entry.endsWith('.prob')) continue;
    const probData = readJsonSafe(path.join(CPH_DIR, entry));
    if (!probData || !probData.srcPath) continue;

    const parentDir = path.dirname(probData.srcPath);
    const folderName = path.basename(parentDir);

    // Only learn from problems already located inside a subfolder (not root)
    if (folderName && folderName !== path.basename(ROOT_DIR) && !IGNORED_DIRS.has(folderName)) {
      if (probData.group) {
        groupToFolder.set(probData.group.trim().toLowerCase(), folderName);
      }
      if (probData.url) {
        const contestMatch = probData.url.match(/contest\/(\d+)/i);
        if (contestMatch) {
          contestToFolder.set(contestMatch[1], folderName);
        }
      }
    }
  }

  return { groupToFolder, contestToFolder };
}

/**
 * Finds the corresponding .prob file in .cph for a given .cpp file at root.
 */
function findProbFileForSource(fileName) {
  if (!fs.existsSync(CPH_DIR)) return null;

  const entries = fs.readdirSync(CPH_DIR);
  const rootSrcPath = getCphPath(path.join(ROOT_DIR, fileName));
  const rootHash = getCphHash(rootSrcPath);
  const expectedProbName = `.${fileName}_${rootHash}.prob`;

  // 1. Direct hash match for the root path
  if (entries.includes(expectedProbName)) {
    const data = readJsonSafe(path.join(CPH_DIR, expectedProbName));
    if (data) return { fileName: expectedProbName, data };
  }

  // 2. Prefix match .<fileName>_*.prob
  const prefix = `.${fileName}_`;
  for (const entry of entries) {
    if (entry.startsWith(prefix) && entry.endsWith('.prob')) {
      const data = readJsonSafe(path.join(CPH_DIR, entry));
      if (data) return { fileName: entry, data };
    }
  }

  // 3. Scan by srcPath basename
  for (const entry of entries) {
    if (!entry.endsWith('.prob')) continue;
    const data = readJsonSafe(path.join(CPH_DIR, entry));
    if (data && data.srcPath && path.basename(data.srcPath) === fileName) {
      return { fileName: entry, data };
    }
  }

  return null;
}

/**
 * Gets all current problem category folders existing in ROOT_DIR.
 */
function getExistingFolders() {
  return fs.readdirSync(ROOT_DIR, { withFileTypes: true })
    .filter(d => d.isDirectory() && !IGNORED_DIRS.has(d.name) && !d.name.startsWith('.'))
    .map(d => d.name);
}

/**
 * Determines the target folder for a problem based on group, url, and aliases.
 */
function determineTargetFolder(probData, fileName, learnedMappings, existingFolders) {
  const group = (probData && probData.group) ? probData.group.trim() : '';
  const url = (probData && probData.url) ? probData.url.trim() : '';
  const lowerGroup = group.toLowerCase();

  // 1. Check learned mappings from other .prob files in .cph
  if (lowerGroup && learnedMappings.groupToFolder.has(lowerGroup)) {
    return learnedMappings.groupToFolder.get(lowerGroup);
  }

  if (url) {
    const contestMatch = url.match(/contest\/(\d+)/i);
    if (contestMatch && learnedMappings.contestToFolder.has(contestMatch[1])) {
      return learnedMappings.contestToFolder.get(contestMatch[1]);
    }
  }

  // 2. Clean topic name (remove "Codeforces - ", etc.)
  let cleanTopic = group
    .replace(/^Codeforces\s*[-:]\s*/i, '')
    .trim();

  // If topic indicates a round
  if (/Codeforces\s*Round/i.test(group) || /Div\.\s*\d+/i.test(group)) {
    cleanTopic = 'Codeforces Rounds';
  }

  const lowerTopic = cleanTopic.toLowerCase();

  // 3. Check known aliases
  if (TOPIC_ALIASES[lowerTopic]) {
    return TOPIC_ALIASES[lowerTopic];
  }

  // 4. Match against existing folders on disk (case-insensitive)
  for (const folder of existingFolders) {
    if (folder.toLowerCase() === lowerTopic) {
      return folder;
    }
  }

  // 5. Fallback: sanitize cleanTopic and use it as the folder name
  if (cleanTopic) {
    const sanitized = cleanTopic.replace(/[<>:"/\\|?*]/g, '').trim();
    if (sanitized) return sanitized;
  }

  return 'Miscellaneous';
}

/**
 * Updates the Problem Catalog section in README.md with newly organized problems.
 */
function updateReadmeCatalog(movedProblems) {
  if (!fs.existsSync(README_PATH) || movedProblems.length === 0) return;

  let readme = fs.readFileSync(README_PATH, 'utf8');

  for (const item of movedProblems) {
    const { folder, fileName, probData } = item;
    if (readme.includes(fileName)) continue;

    const probName = (probData && probData.name) ? probData.name : fileName.replace(/\.cpp$/i, '');
    const probUrl = (probData && probData.url) ? probData.url : '';
    const letterMatch = probName.match(/^([A-Za-z0-9]+)\./);
    const linkLabel = letterMatch ? `Codeforces Problem ${letterMatch[1]}` : (probName || 'Codeforces Link');
    const encodedFolder = encodeURIComponent(folder).replace(/%2F/g, '/');
    const linkColumn = probUrl ? `[${linkLabel}](${probUrl})` : 'Practice Problem';
    const row = `| **${probName}** | [\`${fileName}\`](./${encodedFolder}/${fileName}) | ${linkColumn} |`;

    const escapedFolder = folder.replace(/[-/\\^$*+?.()|[\]{}]/g, '\\$&');
    const sectionRegex = new RegExp(`(###[^\n]*${escapedFolder}[^\n]*\n(?:[^\n]*\n)*?\\|\\s*:---[^\n]*\n)((?:\\|[^\n]*\n)*)`, 'i');
    const match = readme.match(sectionRegex);

    if (match) {
      const headerPart = match[1];
      let rowsPart = match[2];
      rowsPart += row + '\n';
      readme = readme.replace(sectionRegex, headerPart + rowsPart);
    } else {
      const newSection = `\n### 📁 ${folder}\n| Problem | File | Codeforces Link |\n| :--- | :--- | :--- |\n${row}\n`;
      const splitPoint = '## 🛠️ Competitive Programming Helper';
      if (readme.includes(splitPoint)) {
        readme = readme.replace(splitPoint, `${newSection}\n---\n\n${splitPoint}`);
      } else {
        readme += `\n${newSection}`;
      }
    }
  }

  fs.writeFileSync(README_PATH, readme, 'utf8');
}

/**
 * Main function to organize all root .cpp problem files.
 */
function organizeProblems(options = {}) {
  const dryRun = options.dryRun || false;
  console.log(`\n🔍 Scanning for root .cpp problem files in ${ROOT_DIR}...`);

  const rootEntries = fs.readdirSync(ROOT_DIR, { withFileTypes: true });
  const rootCppFiles = rootEntries
    .filter(entry => entry.isFile() && entry.name.toLowerCase().endsWith('.cpp'))
    .map(entry => entry.name);

  if (rootCppFiles.length === 0) {
    console.log('✨ All .cpp files are already organized in their appropriate topic folders! Nothing to do.\n');
    return { movedCount: 0 };
  }

  console.log(`📂 Found ${rootCppFiles.length} problem file(s) at the repository root:\n`);
  for (const f of rootCppFiles) {
    console.log(`   - ${f}`);
  }
  console.log('');

  const learnedMappings = learnExistingMappings();
  const existingFolders = getExistingFolders();
  const movedProblems = [];

  for (const fileName of rootCppFiles) {
    const srcFile = path.join(ROOT_DIR, fileName);
    const probInfo = findProbFileForSource(fileName);

    const probData = probInfo ? probInfo.data : null;
    const targetFolder = determineTargetFolder(probData, fileName, learnedMappings, existingFolders);
    const targetDir = path.join(ROOT_DIR, targetFolder);
    const destFile = path.join(targetDir, fileName);

    const isNewFolder = !fs.existsSync(targetDir);

    console.log(`➡️  Processing: ${fileName}`);
    if (probData) {
      console.log(`   📌 Problem: ${probData.name || 'Unknown'}`);
      console.log(`   🏷️  Group:   ${probData.group || 'None'}`);
    } else {
      console.log(`   ⚠️  No .cph metadata found, placing by naming heuristics.`);
    }

    if (isNewFolder) {
      console.log(`   📁 Target folder "${targetFolder}" does not exist. Creating it...`);
    } else {
      console.log(`   📁 Target folder: "${targetFolder}"`);
    }

    if (dryRun) {
      console.log(`   [DRY RUN] Would move to: ${destFile}\n`);
      continue;
    }

    // 1. Create target directory if needed
    if (!fs.existsSync(targetDir)) {
      fs.mkdirSync(targetDir, { recursive: true });
      existingFolders.push(targetFolder);
    }

    // 2. Move .cpp file
    if (fs.existsSync(destFile)) {
      console.warn(`   ⚠️ Warning: File already exists at ${destFile}. Overwriting...`);
    }
    fs.renameSync(srcFile, destFile);
    console.log(`   ✅ Moved file to ${destFile}`);

    // 3. Update .cph file if present
    if (probInfo) {
      const oldProbPath = path.join(CPH_DIR, probInfo.fileName);
      const newCphSrcPath = getCphPath(destFile);
      const newHash = getCphHash(newCphSrcPath);
      const newProbFileName = `.${fileName}_${newHash}.prob`;
      const newProbPath = path.join(CPH_DIR, newProbFileName);

      probInfo.data.srcPath = newCphSrcPath;

      fs.writeFileSync(newProbPath, JSON.stringify(probInfo.data), { encoding: 'utf8' });
      if (oldProbPath !== newProbPath && fs.existsSync(oldProbPath)) {
        fs.unlinkSync(oldProbPath);
      }
      console.log(`   🔄 Updated .cph metadata -> ${newProbFileName}`);
    }

    movedProblems.push({
      folder: targetFolder,
      fileName,
      probData
    });
    console.log('');
  }

  if (!dryRun && movedProblems.length > 0) {
    // 4. Update README.md catalog
    updateReadmeCatalog(movedProblems);
    console.log('📝 Updated Problem Catalog in README.md.');

    // 5. Update README.md badges & counts
    updateReadme();
    console.log(`\n🎉 Successfully organized ${movedProblems.length} problem(s)!\n`);
  }

  return { movedCount: movedProblems.length };
}

if (require.main === module) {
  const args = process.argv.slice(2);
  const dryRun = args.includes('--dry-run') || args.includes('-n');
  if (args.includes('--help') || args.includes('-h')) {
    console.log(`
Codeforces Problem Organizer

Usage:
  node scripts/organize.js [options]
  npm run organize

Options:
  --dry-run, -n    Preview actions without moving files or modifying metadata
  --help, -h       Display this help message
`);
    process.exit(0);
  }
  organizeProblems({ dryRun });
}

module.exports = { organizeProblems };
