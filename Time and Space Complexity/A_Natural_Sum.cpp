#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    if(!(cin>>n))return 0;
    cout<<n*(n+1)/2;
    return 0;
}