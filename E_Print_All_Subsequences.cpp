#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
void helper(int i,vector<int>&seq,vector<int>&a){
    if(i==a.size()){
        if(!seq.empty()){
            for(int x:seq)cout<<x<<" ";
            cout<<"\n";
    }
    return;
    }
    seq.push_back(a[i]);
    helper(i+1,seq,a);
    seq.pop_back();
    helper(i+1,seq,a);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vector<int>seq;
    helper(0,seq,a);
    return 0;
}