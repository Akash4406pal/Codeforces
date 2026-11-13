#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
using ll=long long;
bool check(const vector<ll>&a,long long x,int k){
    int ptrs=1;
    int time=0;
    for(int i=0;i<a.size();i++){
        if(a[i]>x)return false;
        if(time+a[i]<=x)time+=a[i];
        else {
            time=a[i];
            ptrs++;
        }
        if(ptrs>k)return false;
    }
    return true;
} 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    if(!(cin>>n>>q)){
        return 0;
    }
    vector<ll> a(n);
    ll sum=0;
    for(int i=0;i<n;i++){
        if(!(cin>>a[i])){
            return 0;
        }
        sum+=a[i];
    }
    ll l=*max_element(a.begin(),a.end()),r=sum,ans;
    while(l<=r){
        ll mid=(r-l)/2+l;
        if(check(a,mid,q)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}