#include<iostream>
#include<algorithm>
#include<vector>
#include<cctype>
using namespace std;
bool isVowel(char ch){
    char newCh=tolower(ch);
    if(newCh=='a'||newCh=='e'||newCh=='i'||newCh=='o'||newCh=='u')return true;
    else return false;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    string s;
    if(!(cin>>n>>q)||!(cin>>s))return 0;
    vector<int>track(n+1);
    track[0]=0;
    int i=1;
    for(char ch:s){
        if(isVowel(ch))track[i]=track[i-1]+1;
        else track[i]=track[i-1]-1;
        i++;
    }
    while(q--){
    int l,r;
    if(!(cin>>l>>r))return 0;
    track[r]-track[l-1]==0?cout<<"YES":cout<<"NO";
    cout<<"\n";
}
    return 0;
}