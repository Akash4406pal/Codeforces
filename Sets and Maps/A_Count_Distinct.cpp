#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
using namespace std;
typedef long long ll;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    unordered_set<ll> s(a.begin(), a.end());
    cout << s.size() << "\n";
    return 0;
}