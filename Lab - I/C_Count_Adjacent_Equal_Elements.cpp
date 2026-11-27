#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    cin>>n>>q;
    vector<int>a(n),c(n-1,0),p(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int sum=0;
    for(int i=0;i<n-1;i++){
        if(a[i]==a[i+1])c[i]=1;
        sum+=c[i];
        p[i]=sum;
    }
    while (q--){
        int l,r;
        cin>>l>>r;
        l--;r--;
        if(l==0)cout<<p[r-1];
        else cout<<p[r-1]-p[l-1];
        cout<<"\n";
    }
    
    return 0;
}