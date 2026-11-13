#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
bool canPlace(vector<long long>&a,int k,long long dist){
    int cow=1;
    long long last=a[0];
    for(int i=1;i<a.size();i++){
        if(a[i]-last>=dist){
            cow++;
            last=a[i];
        }
        if(cow==k)return true;
    }
    return false;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k,ans=0;
    if(!(cin>>n>>k))return 0;
    vector<long long>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    int l=0,r=a[n-1]-a[0];
    while(l<=r){
        int mid=l+(r-l)/2;
        if(canPlace(a,k,mid)==true){
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}