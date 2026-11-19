#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    if (!(cin>>n>>q))return 0;
    vector<int>a(n),d(n,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        d[l-1]+=1;
        if(r<n)d[r]-=1;
    }
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=d[i];
        if(sum%2!=0)a[i]^=1;
    }
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}