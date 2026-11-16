#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q,sum=0;
    if(!(cin>>n>>q))return 0;
    vector<int>a(n),p(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(i%2==0)sum+=a[i];
        else sum-=a[i];
        p[i]=sum;
    }
    while(q--){
        int l,r;
        if(!(cin>>l>>r))return 0;
        l--;r--;
        int ans;
        if(l==0)ans=p[r];
        else ans=p[r]-p[l-1];
        if(l%2==0)cout<<ans<<"\n";
        else cout<<ans*-1<<"\n";
    }
    return 0;
}