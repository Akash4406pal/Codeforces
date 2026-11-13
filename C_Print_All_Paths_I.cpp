#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
   void findPaths(int r, int c, int n, int m, string path) {
    if (r == n && c == m) {
        cout << path << "\n";
        return;
    }
    if (c < m) findPaths(r, c + 1, n, m, path + "R");
    if (r < n) findPaths(r + 1, c, n, m, path + "D");
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    if(!(cin>>n>>m))return 0;
    string path;
    findPaths(1,1,n,m,path);
    return 0;
}