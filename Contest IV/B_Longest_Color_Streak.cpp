#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    vector<long long>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int l=0,r=0,ans=1;
    while(r<n){
        while(r+1<n&&a[r+1]==a[r]){
            r++;
        }
        ans=max(ans,r-l+1);
        r++;l=r;
    }
    cout<<ans;
    return 0;
}