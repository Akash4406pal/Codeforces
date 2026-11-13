#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,count=0;
    if(!(cin>>n))return 0;
    for(int i=2;i<=n;i++){
        bool notPrime=false;
        for(int j=2;j*j<=i;j++){
            if(i%j==0){
                notPrime=true;
                break;
            }
        }
         if(!notPrime)count++;
    }
    cout<<count;
    return 0;
}