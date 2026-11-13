#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
void buildComb(int i,string&s,string&path,unordered_map<int,vector<char>>&mpp,vector<string>&ans){
    if(i==s.size()){
        ans.push_back(path);
        return;
    }
    for(int j=0;j<mpp[s[i]-'0'].size();j++){
        path.push_back(mpp[s[i]-'0'][j]);
        buildComb(i+1,s,path,mpp,ans);
        path.pop_back();
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    unordered_map<int,vector<char>>mpp;
    char ch='a';
    for(int i=2;i<=9;i++){
        for(int j=0;j<3;j++){
            mpp[i].push_back(ch);
            ch++;
        }
        if(i==7 || i==9){
            mpp[i].push_back(ch);
            ch++;}
    }
    string s;
    if(!(cin>>s))return 0;
    string comb="";
    vector<string>ans;
    buildComb(0,s,comb,mpp,ans);
    cout<<ans.size()<<"\n";
    for(auto x:ans){
        for(char ch:x){
            cout<<ch;
        }
        cout<<"\n";
    }
    return 0;
}