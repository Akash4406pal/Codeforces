#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    unordered_set<int>unique;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        unique.insert(x);
        cout<<unique.size()<<" ";
    }
    return 0;
}