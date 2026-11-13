#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    if(!(cin>>n))return 0;
    if(n==1){
        cout<<"NO";
        return 0;
    }
    for(long long i=2;i*i<=n;i++){
        if(n%i==0){cout<<"NO";
        return 0;}
    }
    cout<<"YES";
    return 0;
}