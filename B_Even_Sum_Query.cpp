#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define int long long
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q,sum=0;
    if(!(cin>>n))return 0;
    vector<int>a(n),p(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        if((i+1)%2==0)sum+=a[i];
        p[i]=sum;
    }
    if(!(cin>>q))return 0;
    while(q--){
        int l,r;
        if(!(cin>>l>>r))return 0;
        l--;r--;
        if(l==0)cout<<p[r]<<"\n";
        else cout<<p[r]-p[l-1]<<"\n";
    }
    return 0;
}