#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    if(!(cin>>n>>q))return 0;
    vector<int>a(n),pref;
    long long sum=0;
    for(int i=0;i<n;i++){
        if(!(cin>>a[i]))return 0;
        sum+=a[i];
        pref.push_back(sum);
    }
    while(q--){
        int l,r;
        if(!(cin>>l>>r))return 0;
        long long currSum=pref[r-1]-pref[l-1]+a[l-1];
        if((sum-currSum)%2==1)cout<<"YES";
        else cout<<"NO";
        cout<<"\n";
    }
    return 0;
}