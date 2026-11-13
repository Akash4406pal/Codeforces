#include<iostream>
#include<algorithm>
#include<vector>
#include<cctype>
using namespace std;
bool isVowel(char ch){
    ch=tolower(ch);
    if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u')return true;
    else return false;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    if(!(cin>>n>>k))return 0;
    string s;
    cin>>s;
    int l=0,r=0,count=0;
    while(r<n){
        if(isVowel(s[r++]))count++;
        if(r-l==k){
            cout<<count<<" ";
            if(isVowel(s[l]))count--;
            l++;
        }
    }
    return 0;
}