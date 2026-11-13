const fs = require('fs');
const path = require('path');

const ROOT_DIR = path.resolve(__dirname, '..');
const README_PATH = path.join(ROOT_DIR, 'README.md');

// Directories to ignore when scanning for problem solutions
const IGNORED_DIRS = new Set([
  '.git',
  '.github',
  '.cph',
  '.vscode',
  '.idea',
  'scripts',
  'node_modules'
]);

function getFileCountByTopic() {
  const entries = fs.readdirSync(ROOT_DIR, { withFileTypes: true });
  const counts = new Map();

  for (const entry of entries) {
    if (!entry.isDirectory() || IGNORED_DIRS.has(entry.name) || entry.name.startsWith('.')) {
      continue;
    }

    const folderPath = path.join(ROOT_DIR, entry.name);
    try {
      const files = fs.readdirSync(folderPath);
      // Count solution files (.cpp, .cc, .cxx, .py, .java)
      const solutionFiles = files.filter(f => /\.(cpp|cc|cxx|py|java)$/i.test(f));
      counts.set(entry.name, solutionFiles.length);
    } catch (err) {
      console.warn(`Could not read directory ${entry.name}:`, err.message);
    }
  }

  return counts;
}

function readReadme(filePath) {
  let buffer = fs.readFileSync(filePath);

  // If buffer starts with UTF-16 LE BOM (0xFF 0xFE)
  if (buffer.length >= 2 && buffer[0] === 0xff && buffer[1] === 0xfe) {
    if (buffer.length >= 4 && buffer[3] !== 0x00) {
      // Erroneous 2-byte BOM on UTF-8 text
      buffer = buffer.slice(2);
    } else {
      // Real UTF-16 LE
      return buffer.slice(2).toString('utf16le');
    }
  }

  // If buffer starts with UTF-8 BOM (0xEF 0xBB 0xBF)
  if (buffer.length >= 3 && buffer[0] === 0xef && buffer[1] === 0xbb && buffer[2] === 0xbf) {
    buffer = buffer.slice(3);
  }

  let content = buffer.toString('utf8');
  if (content.charCodeAt(0) === 0xfeff) {
    content = content.slice(1);
  }
  return content;
}

function updateReadme() {
  const counts = getFileCountByTopic();
  let totalSolved = 0;
  for (const count of counts.values()) {
    totalSolved += count;
  }
  const totalTopics = counts.size;

  console.log(`📊 Discovered ${totalTopics} topics with ${totalSolved} total solved problems:`);
  for (const [topic, count] of counts.entries()) {
    console.log(`   - ${topic}: ${count}`);
  }

  let readme = readReadme(README_PATH);

  // 1. Update or inject shields.io badges
  const today = new Date().toISOString().split('T')[0];
  const badgesHtml = [
    `<!-- BADGES:START -->`,
    `[![Problems Solved](https://img.shields.io/badge/Problems%20Solved-${totalSolved}-brightgreen?style=flat-square&logo=codeforces)](./README.md)`,
    `[![Topics](https://img.shields.io/badge/Topics-${totalTopics}-blue?style=flat-square)](./README.md)`,
    `[![Last Updated](https://img.shields.io/badge/Last%20Updated-${today}-orange?style=flat-square)](./README.md)`,
    `<!-- BADGES:END -->`
  ].join('\n');

  if (readme.includes('<!-- BADGES:START -->') && readme.includes('<!-- BADGES:END -->')) {
    readme = readme.replace(/<!-- BADGES:START -->[\s\S]*?<!-- BADGES:END -->/, badgesHtml);
  } else {
    // Insert badges right after the main H1 header
    readme = readme.replace(/(# [^\n]+)(\n\s*\n)?/, `$1\n\n${badgesHtml}\n\n`);
  }

  // 2. Parse and update the Overview table
  const lines = readme.split(/\r?\n/);
  const updatedLines = [];
  let inOverviewSection = false;
  let inTable = false;
  let seenTopicsInTable = new Set();

  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];

    if (/^##\s*📁\s*Repository Overview/i.test(line)) {
      inOverviewSection = true;
      updatedLines.push(line);
      continue;
    }

    if (inOverviewSection && !inTable) {
      if (line.trim().startsWith('| Topic / Folder')) {
        inTable = true;
        updatedLines.push(line);
        continue;
      }
      updatedLines.push(line);
      continue;
    }

    if (inTable) {
      // Alignment row: | :--- | :---: | :--- |
      if (line.trim().startsWith('| :---')) {
        updatedLines.push(line);
        continue;
      }

      // Check for topic row: | [Topic](./Path) | count | desc |
      const rowMatch = line.match(/^\|\s*\[([^\]]+)\]\(([^)]+)\)\s*\|\s*([^|]+)\s*\|\s*([^|]+)\s*\|$/);
      if (rowMatch) {
        const linkText = rowMatch[1].trim();
        const linkTarget = rowMatch[2].trim();
        const folderName = decodeURIComponent(linkTarget.replace(/^\.\//, ''));
        const desc = rowMatch[4].trim();

        seenTopicsInTable.add(folderName);
        const actualCount = counts.has(folderName) ? counts.get(folderName) : 0;
        updatedLines.push(`| [${linkText}](${linkTarget}) | ${actualCount} | ${desc} |`);
        continue;
      }

      // Existing Total row - ignore so we can re-append at the end of the table
      if (line.match(/^\|\s*\*\*Total\*\*\s*\|/i)) {
        continue;
      }

      // If a non-table line is encountered, the table has ended
      if (!line.trim().startsWith('|')) {
        // Append any new folders found on disk that weren't in the table yet
        for (const [topic, count] of counts.entries()) {
          if (!seenTopicsInTable.has(topic)) {
            const encodedPath = './' + encodeURIComponent(topic).replace(/%2F/g, '/');
            updatedLines.push(`| [${topic}](${encodedPath}) | ${count} | ${topic} practice problems |`);
          }
        }
        // Append Total row
        updatedLines.push(`| **Total** | **${totalSolved}** | **All Categories Combined** |`);

        inTable = false;
        inOverviewSection = false;
        updatedLines.push(line);
        continue;
      }
    }

    updatedLines.push(line);
  }

  if (inTable) {
    for (const [topic, count] of counts.entries()) {
      if (!seenTopicsInTable.has(topic)) {
        const encodedPath = './' + encodeURIComponent(topic).replace(/%2F/g, '/');
        updatedLines.push(`| [${topic}](${encodedPath}) | ${count} | ${topic} practice problems |`);
      }
    }
    updatedLines.push(`| **Total** | **${totalSolved}** | **All Categories Combined** |`);
  }

  const finalContent = updatedLines.join('\n');
  fs.writeFileSync(README_PATH, finalContent, { encoding: 'utf8' });
  console.log(`✅ README.md successfully updated in clean UTF-8 format! (Total: ${totalSolved})`);
}

if (require.main === module) {
  updateReadme();
}

module.exports = { updateReadme };
