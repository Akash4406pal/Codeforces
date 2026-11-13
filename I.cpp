#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void buildpath(int i,int sum,int n,vector<int>&path){
    path.push_back(i);
    sum+=i;
    if(sum>=n){
        if(sum==n){for(int x:path)cout<<x<<" ";
        cout<<"\n";}
        path.pop_back();
        return;
    }
    buildpath(1,sum,n,path);
    buildpath(2,sum,n,path);
    path.pop_back();
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    vector<int>x;
    buildpath(1,0,n,x);
    buildpath(2,0,n,x);
    return 0;
}