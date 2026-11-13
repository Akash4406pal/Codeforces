#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        int n,x,ans=0;
        cin>>n;
        vector<int>a(n);
        unordered_map<int,int>freq;
        for(int i=0;i<n;i++){
            cin>>a[i];
            freq[a[i]]++;
        }
        cin>>x;
        for(int i=0;i<n;i++){
            int tar=x-a[i];
            ans+=freq[x-a[i]];
            if(tar==a[i])ans-=1;
        }
        cout<<ans/2<<"\n";
    }
    return 0;
}