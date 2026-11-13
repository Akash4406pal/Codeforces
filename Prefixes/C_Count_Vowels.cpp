#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q;
    string s;
    if(!(cin>>n)||!(cin>>s)||!(cin>>q))return 0;
    vector<int>vowels(n,0);
    if(s[0]=='a'||s[0]=='e'||s[0]=='i'||s[0]=='o'||s[0]=='u')vowels[0]=1;
    for(int i=1;i<n;i++){
        if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')vowels[i]=vowels[i-1]+1;
        else vowels[i]=vowels[i-1];
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<vowels[r-1]-vowels[l-1]+(s[l-1]=='a'||s[l-1]=='e'||s[l-1]=='i'||s[l-1]=='o'||s[l-1]=='u')?1:0;
        cout<<"\n";
    }
    return 0;
}