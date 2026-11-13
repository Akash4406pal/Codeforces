#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    if(!(cin>>n>>k))return 0;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    unordered_map<int,int>mpp;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
    if (k == 0) {
        if (a[i] == 0) {
            ans += i;
        }
    } else {
        if (a[i] % k == 0) {
            int target = a[i] / k;
            if (mpp.count(target)) {
                ans += mpp[target];
            }
        }
    }
    mpp[a[i]]++;
}
    cout<<ans;
    return 0;
}