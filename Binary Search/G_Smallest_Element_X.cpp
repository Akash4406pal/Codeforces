#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    if(!(cin>>n>>q))return 0;
    vector<long long>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a.begin(),a.end());
    while(q--){
        int x;
        cin>>x;
        auto lb_it=lower_bound(a.begin(),a.end(),x);
        if(lb_it!=a.end())cout<<*lb_it;
        else cout<<-1;
        cout<<"\n";
    }
    return 0;
}