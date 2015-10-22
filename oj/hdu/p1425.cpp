#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int cmp(int x,int y){
	if(x < y) return 1;
	return 0;
}

const int MX = 1000080;
int num[MX];
int  main(){
    int n,m;
    while(scanf("%d%d",&n,&m)){
        for(int i = 0; i < n; i++) scanf("%d",&num[i]);
        sort(num,num+n,cmp);
        for(int i = 0; i < m; i++){
            if(i) printf("%d",num[n-1-i]);
            else printf(" %d",num[n-1-i]);
        }
        puts("");

    }
    return 0;
}
