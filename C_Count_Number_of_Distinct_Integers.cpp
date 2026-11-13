#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k,l=0,r=0;
    if(!(cin>>n>>k))return 0;
    vector<long long>a(n);
    unordered_map<long long,int>mpp;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    while(r<n){
      mpp[a[r++]]++;
      if(r-l==k){
        cout<<mpp.size()<<" ";
        if(mpp[a[l]]-1==0)mpp.erase(a[l]);
        else mpp[a[l]]-=1;
        l++;
    }
      }
    return 0;
}