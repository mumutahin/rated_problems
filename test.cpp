#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    for(int z=0;z<t;z++){
        int n,f=0;
        cin>>n;
        int a[n];
        for(int i=0;i<n;i++)cin>>a[i];
        if(a[0]%2==0){
            for(int i=0;i<n;i++)if(a[i]%2==0)f++;
            if(f!=n){
                f=0;
                for(int i=0;i<n;i++){
                    if(a[i]%2==0 && i%2==0)f++;
                    if(a[i]%2!=0 && i%2!=0)f++;
                }
            }
        }
        else if(a[0]%2!=0){
            for(int i=0;i<n;i++)if(a[i]%2!=0)f++;
            if(f!=n){
                f=0;
                for(int i=0;i<n;i++){
                    if(a[i]%2!=0 && i%2==0)f++;
                    if(a[i]%2==0 && i%2!=0)f++;
                }
            }
        }
        if(f==n)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}