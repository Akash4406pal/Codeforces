#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void helper(int i,vector<int>&seq,vector<int>&a,int k,int sum,vector<vector<int>>&ans){
    if(i==a.size()){
        if(sum==k){
            ans.push_back(seq);
        }
    return;
    }
    seq.push_back(a[i]);
    sum+=a[i];
    helper(i+1,seq,a,k,sum,ans);
    seq.pop_back();
    sum-=a[i];
    helper(i+1,seq,a,k,sum,ans);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    if(!(cin>>n>>k))return 0;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vector<int>seq;
    vector<vector<int>>ans;
    helper(0,seq,a,k,0,ans);
    cout<<ans.size()<<"\n";
    for(auto x:ans){
        for(int y:x)cout<<y<<" ";
        cout<<"\n";
    }
    return 0;
}