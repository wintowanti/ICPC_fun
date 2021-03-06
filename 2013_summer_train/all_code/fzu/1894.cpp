#include<cstdio>
#define M 2000000
int my_queue[M];
int a[M];
int l,r;
int main(){
    int cas;while(~scanf("%d",&cas)){
        while(cas--){
            l=0;r=-1;
            int num=0;
            int time=0;
            while(1){
                char str[100];
                scanf("%s",str);
                if(str[0]=='E') break;
                else if(str[0]=='C'){
                    int t1;scanf("%s%d",str,&t1);
                    a[num]=t1;
                    while(l<=r&&t1>a[my_queue[r]]){
                        r--;
                    }
                    my_queue[++r]=num++;
                }
                else if(str[0]=='Q'){
                    if(l<=r){
                        printf("%d\n",a[my_queue[l]]);
                    }
                    else puts("-1");
                }
                else if(str[0]=='G'){
                    if(my_queue[l]<=time) l++;
                    time++;
                }
            }
        }
    }
    return 0;
}
