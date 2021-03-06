#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<functional>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
#define M 108000
#define pf printf("~~~~~~~~~~~~~\n");
#define pn printf("\n");
#define inf 0x3f3f3f3f
#define ll long long
  using namespace std;
  const int Ni = 700;
  const int MAX = 1<<26;
  struct Edge{
      int u,v,c;
      int next;
  }edge[Ni*Ni];
  int edn;//����
  int p[Ni];//����
  int d[Ni];
  int sp,tp;//ԭ�㣬���
    ll map1[Ni][Ni];
    ll tmax=0;
    ll tsum=0;
  void addedge(int u,int v,int c)
  {
      edge[edn].u=u; edge[edn].v=v; edge[edn].c=c;
      edge[edn].next=p[u]; p[u]=edn++;

      edge[edn].u=v; edge[edn].v=u; edge[edn].c=0;
      edge[edn].next=p[v]; p[v]=edn++;
  }
  int bfs()
  {
      queue <int> q;
      memset(d,-1,sizeof(d));
      d[sp]=0;
      q.push(sp);
      while(!q.empty())
      {
          int cur=q.front();
          q.pop();
          for(int i=p[cur];i!=-1;i=edge[i].next)
          {
              int u=edge[i].v;
              if(d[u]==-1 && edge[i].c>0)
              {
                  d[u]=d[cur]+1;
                  q.push(u);
              }
          }
      }
      return d[tp] != -1;
  }
  int dfs(int a,int b)
  {
      int r=0;
      if(a==tp)return b;
      for(int i=p[a];i!=-1 && r<b;i=edge[i].next)
      {
          int u=edge[i].v;
          if(edge[i].c>0 && d[u]==d[a]+1)
          {
              int x=min(edge[i].c,b-r);
              x=dfs(u,x);
              r+=x;
              edge[i].c-=x;
              edge[i^1].c+=x;
          }
      }
      if(!r)d[a]=-2;
      return r;
  }

  int dinic(int sp,int tp)
  {
      int total=0,t;
      while(bfs())
      {
          while(t=dfs(sp,MAX))
          total+=t;
      }
      return total;
  }
  void init(){
    memset(p,-1,sizeof(p));edn=0;
  }
  void floyd(int n){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(map1[i][j]>map1[i][k]+map1[k][j]){
                    map1[i][j]=map1[i][k]+map1[k][j];
                }
            }
        }
    }
 }
 int door[M][2];
 int build(ll mid,int n){
     init();
    sp=0;
    tp=2*n+1;
     for(int i=1;i<=n;i++){
        int t1=door[i][0];
        int t2=door[i][1];
        addedge(sp,i,t1);
        addedge(i+n,tp,t2);
        addedge(i,i+n,inf);
     }
     for(int i=1;i<=n;i++){
            if(door[i][0]==0) continue;
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            if(map1[i][j]<=mid){
                if(map1[i][j]>tmax) continue ;
                addedge(i,j+n,door[i][0]);
            }
        }
     }
  //   printf("******\n");
     int t1=dinic(sp,tp);
  //   printf("%d\n",t1);
     if(t1<tsum) return 0;
     return 1;
 }
 ll binary(ll l,ll r,int n){
     ll tmin=inf*1000ll,mid;
     while(r>=l){
        mid=(l+r)>>1;
    //    printf("%lld   %lld   %lld\n",l,r,mid);
        if(build(mid,n)){
            tmin=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
     }
     return tmin;
 }
 int main()
 {
     int n,m;
     while(~scanf("%d%d",&n,&m))
     {
         tsum=0;
         int tsum2=0;
         tmax=0;
         for(int i=1;i<=n;i++){
            scanf("%d%d",&door[i][0],&door[i][1]);
            tsum+=door[i][0];
            tsum2+=door[i][1];
         }
         memset(map1,inf,sizeof(map1));
         for(int i=0;i<m;i++){
            int t1,t2,t3;scanf("%d%d%d",&t1,&t2,&t3);
            if(map1[t1][t2]>t3) map1[t1][t2]=t3,map1[t2][t1]=t3;
            tmax+=t3;
         }
         if(tsum2<tsum){
            puts("-1");
         }
         floyd(n);
     //    printf("~~~~~~~~~~~~~~~~~\n");
         ll ans=binary(0,tmax,n);
         if(ans>inf*1000ll){
            puts("-1");
         }
         else{
            printf("%lld\n",ans);
         }
     }
     return 0;
 }
