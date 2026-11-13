#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void buildpath(int i,int sum,int n,int k,vector<int>&path){
    path.push_back(i);
    sum+=i;
    if(sum>=n){
        if(sum==n){for(int x:path)cout<<x<<" ";
        cout<<"\n";}
        path.pop_back();
        return;
    }
    for(int i=1;i<=k;i++){
    buildpath(i,sum,n,k,path);
    }
    path.pop_back();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    if(!(cin>>n>>k))return 0;
    vector<int>x;
    for(int i=1;i<=k;i++)buildpath(i,0,n,k,x);
    return 0;
}