#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    if(!(cin>>n>>m))return 0;
    int nlastd=n%10;
    int mlastc=m%10;
    cout<<mlastc+nlastd;
    return 0;
}