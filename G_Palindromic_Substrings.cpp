#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if(!(cin>>n))return 0;
    string s;
    if(!(cin>>s))return 0;
    for(int i=0;i<n;i++){
        for(int j=1;j<=n-i;j++){
            string subS=s.substr(i,j);
            int r=subS.size()-1,l=0;
            bool is_palidrom=true;
            while(l<r){
                if(subS[l]!=subS[r]){
                    is_palidrom=false;
                    break;}
                l++;r--;
            }
            if(is_palidrom){
                cout<<subS<<"\n";
            }
        }
    }
    return 0;
}