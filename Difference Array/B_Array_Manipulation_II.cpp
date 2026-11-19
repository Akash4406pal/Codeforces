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
    vector<int>a(n),p(n,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    while(q--){
        int l,r,k;
        cin>>l>>r>>k;
        p[l-1]+=k;
        if(r<n)p[r]-=k;
    }
    int maxi=0,sum=0;
    for(int i=0;i<n;i++){
        sum+=p[i];
        maxi=max(maxi,sum+a[i]);
    }
    cout<<maxi<<"\n";
    return 0;
}