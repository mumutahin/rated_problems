#include<bits/stdc++.h>
using namespace std;

int main(){
    int a,b;
    cin>>a>>b;
    int pro=a*b;
    int sum=a+b;
    int sub=a-b;
    if(pro>=sum && pro>=sub)cout<<pro<<endl;
    if(sum>=pro && sum>=sub)cout<<sum<<endl;
    if(sub>=pro && sub>=sum)cout<<sub<<endl;
    return 0;
}