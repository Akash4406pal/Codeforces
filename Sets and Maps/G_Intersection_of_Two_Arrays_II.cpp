#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
typedef long long ll;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    unordered_map<long long,int>mpp;
    if(!(cin>>n))return 0;
    vector<ll>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        mpp[a[i]]++;}
    if(!(cin>>m))return 0;
    vector<ll>b(m),ans;
    for(int i=0;i<m;i++){
    cin>>b[i];
    if(mpp[b[i]]>0){
        ans.push_back(b[i]);
        mpp[b[i]]--;
    }
    }
    cout<<ans.size()<<"\n";
    sort(ans.begin(),ans.end());
    for(ll x:ans)cout<<x<<" ";
    return 0;
}