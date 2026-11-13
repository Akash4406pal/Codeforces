#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    long long sum=0,ans=0;
    vector<long long>pref,a(n);
    for(int i=0;i<n;i++){
        if(!(cin>>a[i]))return 0;
        sum+=a[i];
        pref.push_back(sum);
    }
    for(int i=1;i<n;i++){
        if(pref[i-1]==pref[n-1]-pref[i])ans+=1;
    }
    if(pref[n-1]==a[0])ans++;
    cout<<ans;
    return 0;
}