#include<stdio.h>

int main(){
    int n, m, x,y=0;
    scanf("%d%d", &n, &m);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d",&x);
        for(int j=0;j<n;j++){
            if(x==a[j]){
                printf("found\n");
                y++;
            }
        }
        if(y==0)printf("not found\n");
        y=0;
    }
    return 0;
}