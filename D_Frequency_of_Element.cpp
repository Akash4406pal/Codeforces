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
    unordered_map<long long,int>freq;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        freq[a[i]]++;
    }
    while(q--){
        int x;
        cin>>x;
        cout<<freq[x]<<"\n";
    }
return 0;
}