#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    if(!(cin>>q))return 0;
    while(q--){
        long long l,r;
        if(!(cin>>l>>r))return 0;
        long long ans=(r*(r+1)-l*(l-1))/2;
        cout<<ans<<"\n";
    }
    return 0;
}