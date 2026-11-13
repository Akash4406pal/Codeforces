#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void findPaths(int r, int c, int n, int m, string&path,vector<vector<int>>&g) {
    if (r == n && c == m) {
        cout << path << "\n";
        return;
    }
    if(g[r-1][c-1]==1)return;

    if (c < m){
        path.push_back('R');
        findPaths(r, c + 1, n, m, path,g);
        path.pop_back();
    } 
    if (r < n){
        path.push_back('D');
        findPaths(r + 1, c, n, m, path,g);
        path.pop_back();
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    if(!(cin>>n>>m))return 0;
    vector<vector<int>>grid(n,vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>grid[i][j];
        }
    }
    string path;
    findPaths(1,1,n,m,path,grid);
    return 0;
}