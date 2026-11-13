#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a,b;
    if(!(cin>>a>>b))return 0;
    long long countA=0,countB=0;
    for(long long i=1;i*i<=(a);i++){
        if(a%i==0)countA+=a/i==a?1:2;
    }
    for(long long i=1;i*i<=b;i++){
        if(b%i==0)countB+=b/i==b?1:2;
    }
    if(countA>countB)cout<<"A";
    else if(countA<countB)cout<<"B";
    else cout<<"DRAW";
    return 0;
}