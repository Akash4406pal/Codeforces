#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int countDigits(int x){
    int sum=0;
    while(x!=0){
        sum+=x%10;
        x/=10;
    }
    return sum;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q,k,count=0;
    if(!(cin>>n>>q>>k))return 0;
    vector<int>a(n),p(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(countDigits(a[i])==k)count++;
        p[i]=count;
    }
    while(q--){
        int l,r;
        if(!(cin>>l>>r))return 0;
        l--;r--;
        if(l==0)cout<<p[r]<<"\n";
        else cout<<p[r]-p[l-1]<<"\n";
    }
    return 0;
}