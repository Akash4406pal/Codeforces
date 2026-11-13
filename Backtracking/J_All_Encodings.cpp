#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
void helper(int i,string&s,vector<string>&ans,string&path){
    if(i==s.size()){ans.push_back(path);return;}
    path.push_back(char('a'+int(s[i]-'1')));
    helper(i+1,s,ans,path);
    path.pop_back();
    if(s[i]<'3' && i+1<s.size()){
        if(stoi(s.substr(i, 2))<=26){
            path.push_back(char('a'+stoi(s.substr(i, 2))-1));
            helper(i+2,s,ans,path);
            path.pop_back();
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    if(!(cin>>s))return 0;
    vector<string>ans;
    string curr;
    helper(0,s,ans,curr);
    cout<<ans.size()<<"\n";
    for(auto x:ans){
        for(char ch:x){
            cout<<ch;
        }
        cout<<"\n";
    }
    return 0;
}