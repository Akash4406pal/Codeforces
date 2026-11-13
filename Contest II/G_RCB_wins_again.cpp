#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    vector<long long>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int midr=n/2,midl=midr-1;
    while(midl>=0 && midr<n){
        cout<<a[midl]<<" ";
        midl--;
        cout<<a[midr]<<" ";
        midr++;
    }
    return 0;
}