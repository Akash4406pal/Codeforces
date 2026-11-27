#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int count1s(vector<int>&x,int l,int r){
    if(l==0)return x[r];
    else return x[r]-x[l-1];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    if(!(cin>>n>>q))return 0;;
    vector<int>a(n),c(n-1,0),p(n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n-1;i++){
        if(a[i]==a[i+1])c[i]=1;
    }
    int sum=0;
    for(int i=0;i<n-1;i++){
        sum+=c[i];
        p[i]=sum;
    }
    while (q--){
        int l,r;
        if(!(cin>>l>>r))return 0;
        l--;r--;
        if(r==l){
            cout<<"YES"<<"\n";
            continue;
        }
        int count=count1s(p,l,r-1);
        if(count==r-l)cout<<"YES";
        else cout<<"NO";
        cout<<"\n";
    }
    return 0;
}