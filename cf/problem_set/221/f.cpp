/***************************************************
   #>File Name: f.cpp
   #>Auther: wintowanti
   #>Mail: wintowanti@163.com
   #>Created Time: 2014/1/3 21:07:19
***************************************************/

#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>
#include<algorithm>
#include<stack>
#include<vector>
#include<queue>
#include<cmath>
#include<set>

using namespace std ;

#define int int
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define it iterator
#define mt(a,b) memset(a,b,sizeof(a))

typedef pair<int,int> pii;
typedef long long ll;

const int INF=0x3f3f3f3f;
const int MV=100008;
const int ME=2000006;
const int MOD=1000000007;

vector<int> g1[MV];
int lowbit(int x){
	return x&(-x);
}
map<int,int>::it it1,it2;
struct BIT{
	map<int,int> sum;
	map<int,int> color;
	int size;
	void merge(BIT &y){
		for(it1=y.color.begin();it1!=y.color.end();it1++){
			int c1=it1->ft;
			int s1=it1->sd;
			int & s2=color[c1];
			if(s2!=0){
				update(s2,-1);
			}else size++;
			s2+=s1;
			update(s2,1);
		}
	}
	void update(int x,int value){
		while(x<MV){
			sum[x]+=value;
			x+=lowbit(x);
		}
	}
	int getsum(int x){
		int tsum=0;
		while(x>0){
			tsum+=sum[x];
			x-=lowbit(x);
		}
		return tsum;
	}
}bit[MV];
struct Q{
	int id,k;
};
vector<Q> query[MV];
int fcolor[MV];
int ans[MV];
void dfs(int u,int fa){
	bit[u].color[fcolor[u]]=1;
	bit[u].update(1,1);
	bit[u].size=1;
	for(int i=0;i<g1[u].size();i++){
		int v=g1[u][i];
		if(v==fa) continue;
		dfs(v,u);
		if(bit[v].size>bit[u].size){
			swap(bit[v],bit[u]);
		}
		bit[u].merge(bit[v]);
		bit[v].sum.clear();
		bit[v].color.clear();
	}
	for(int i=0;i<query[u].size();i++){
		Q q1;q1=query[u][i];
		ans[q1.id]=bit[u].size-bit[u].getsum(q1.k-1);
	}
}
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		for(int i=0;i<=n;i++){
			g1[i].clear();
			query[i].clear();
			bit[i].sum.clear();
			bit[i].color.clear();
		}
		for(int i=1;i<=n;i++) scanf("%d",&fcolor[i]);
		for(int i=1;i<n;i++){
			int u,v;scanf("%d%d",&u,&v);
			g1[u].pb(v);
			g1[v].pb(u);
		}
		for(int i=0;i<m;i++){
			int u,k;scanf("%d%d",&u,&k);
			Q q1;q1.k=k;q1.id=i;
			query[u].pb(q1);
		}
		dfs(1,-1);
		for(int i=0;i<m;i++){
			printf("%d\n",ans[i]);
		}
		int t1;
	}
	return 0;
}
