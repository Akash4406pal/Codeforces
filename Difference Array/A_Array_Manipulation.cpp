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
    vector<int>a(n,0);
    while(q--){
        int l,r,k;
        cin>>l>>r>>k;
        a[l-1]+=k;
        if(r<n)a[r]-=k;
    }
    int maxi=0,sum=0;
    for(int i=0;i<n;i++){
        sum+=a[i];
        maxi=max(maxi,sum);
    }
    cout<<maxi<<"\n";
    return 0;
}