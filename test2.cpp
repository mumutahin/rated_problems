#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        if(b-(a-b)==0)cout<<0<<endl;
        else if(b-(a-b)!=0)cout<<abs(a-b)<<endl;
    }
    return 0;
}