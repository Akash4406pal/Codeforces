#include <iostream>
#include <vector>
#include <algorithm>
#include<unordered_map>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    if(!(cin>>n>>q))return 0;
    if(n<0 || q<0)return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    while(q--){
        int x;
        cin>>x;
        auto lb_it=lower_bound(a.begin(),a.end(),x);
        cout<<a.end()-lb_it<<"\n";
    }
return 0;
}