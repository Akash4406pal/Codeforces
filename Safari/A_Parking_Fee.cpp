#include<iostream>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int h1,h2,m1,m2;
    if(!(cin>>h1>>m1))return 0;
    if(!(cin>>h2>>m2))return 0;
    if(h2<h1)return 0;
    int totalM=(h2-h1)*60+(m2-m1);
    int totalPayM=totalM-120;
    if(totalPayM<=0)cout<<0;
    else{int extra=totalPayM%60>0?20:0;
    cout<<min(totalPayM/60*20+extra,100);}
    return 0;
}