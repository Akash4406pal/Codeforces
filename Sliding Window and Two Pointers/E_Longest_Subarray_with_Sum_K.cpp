#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long k;
    if(!(cin>>n>>k))return 0;
    vector<long long>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    int l=0,r=0,ans=0;
    long long sum=0;
    while(r<n){
        sum+=a[r++];
        while(sum>=k){
            sum-=a[l];
            l++;
        }
        ans=max(ans,r-l);
    }
    cout<<ans;
    return 0;
}