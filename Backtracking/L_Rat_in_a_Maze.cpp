#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void helper(int i,int j,vector<vector<int>>&a,vector<string>&ans,string&path,vector<vector<bool>>&vis){
    if(i==a.size()-1 && j==a.size()-1){
        ans.push_back(path);
        return;
    }
    if(i+1<a.size() && a[i+1][j]==1 && vis[i+1][j]==false){
        path.push_back('D');
        vis[i+1][j]=true;
        helper(i+1,j,a,ans,path,vis);
        path.pop_back();
        vis[i+1][j]=false;
    }
    if(j-1>=0 && a[i][j-1]==1 && vis[i][j-1]==false){
        path.push_back('L');
        vis[i][j-1]=true;
        helper(i,j-1,a,ans,path,vis);
        path.pop_back();
        vis[i][j-1]=false;
    }
    if(j+1<a.size() && a[i][j+1]==1 && vis[i][j+1]==false){
        path.push_back('R');
        vis[i][j+1]=true;
        helper(i,j+1,a,ans,path,vis);
        path.pop_back();
        vis[i][j+1]=false;
    }
    if(i-1>=0 && a[i-1][j]==1 && vis[i-1][j]==false){
        path.push_back('U');
        vis[i-1][j]=true;
        helper(i-1,j,a,ans,path,vis);
        path.pop_back();
        vis[i-1][j]=false;
    }
    
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    vector<vector<int>>a(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    if(a[0][0]==0||a[n-1][n-1]==0){cout<<0;return 0;}
    vector<vector<bool>>vis(n,vector<bool>(n));
    vis[0][0]=true;
    string path="";
    vector<string>ans;
    helper(0,0,a,ans,path,vis);
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<"\n";
    if(ans.size()>0)for(auto x:ans){
        cout<<x<<"\n";
    }
    return 0;
}