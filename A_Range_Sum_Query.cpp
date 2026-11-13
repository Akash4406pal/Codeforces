#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    if(!(cin>>n))return 0;
    vector<long long>a(n);
    vector<long long>preSum(n);
    long long sum=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        preSum[i]=sum;
        sum+=a[i];
    }
    if(!(cin>>q))return 0;
    while(q--){
        int l,r;
        if(!(cin>>l>>r))return 0;
        cout<<preSum[r-1]-preSum[l-1]+a[r-1]<<"\n";
    }
    return 0;
}