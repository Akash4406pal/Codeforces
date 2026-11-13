#include<iostream>
#include<algorithm>
#include<vector>
#include <climits>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k,i=0,j=0;
    long long ans=LLONG_MIN,sum=0;
    if(!(cin>>n>>k))return 0;
    vector<long long>a(n);
    for(int x=0;x<n;x++){
        cin>>a[x];
    }
    while(j<n){
       sum+=a[j];
       j++;
       if(j-i==k){
        ans=max(ans,sum);
        sum-=a[i];
        i++;
       }
    }
    cout<<ans<<"\n";
    return 0;
}