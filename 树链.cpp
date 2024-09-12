#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod (1000000007)
#define PII pair<int,int>
#define F first
#define S second
#define N 200005
//f（父节点）、sz（子树大小）、dep（深度）、hson（重子节点）,dfsn (dfs序)，rdfsn (最大dfs序) , top (树链根节点)
ll n,m,a[N],b[N],RT=1,dep[N],sz[N],f[N],hson[N],dfsn[N],cnt,rdfsn[N],top[N];
vector<int>e[N];
struct Tree{
	int l,r;
	ll len,sm=0,vis=0;
}t[N<<2];
void dfs1(int u,int d=1){
	int size=1,mx_son=0;
	dep[u]=d;
	for(auto v:e[u]){
		if(!dep[v]){
			f[v]=u;
			dfs1(v,d+1);
			size+=sz[v];
			if(sz[v]>mx_son){
				mx_son=sz[v];
				hson[u]=v;
			}
		}
	}
	sz[u]=size;
}
void dfs2(int u){
	dfsn[u]=++cnt;
	if(hson[u]){
		top[hson[u]]=top[u];
		dfs2(hson[u]);
	}
	for(auto v:e[u]){
		if(!top[v]){
			top[v]=v;
			dfs2(v);
		}
	}
	rdfsn[u]=cnt;
}
int lca(int x,int y){      
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])x=f[top[x]];
		else y=f[top[y]];
	}
	return (dep[x]>dep[y]?y:x);
}
void build(int l=1,int r=n,int id=1){
	t[id]={l,r,r-l+1};
	if(l==r){
		t[id].sm=b[l];
		return;
	}
	int mid=l+r>>1;
	build(l,mid,id<<1);
	build(mid+1,r,id<<1|1);
	t[id].sm=t[id<<1].sm+t[id<<1|1].sm;
}
void push_down(int id){  //懒标记下传 
	if(!t[id].vis)return;
	t[id<<1].vis=t[id<<1].vis+t[id].vis;
	t[id<<1|1].vis=t[id<<1|1].vis+t[id].vis;
	t[id<<1].sm=t[id<<1].sm+t[id].vis*t[id<<1].len;
	t[id<<1|1].sm=t[id<<1|1].sm+t[id].vis*t[id<<1|1].len;
	t[id].vis=0;
}
void update(int l,int r,int w,int L=1,int R=n,int id=1){
	if(l>R||r<L)return;
	if(l<=L&&R<=r){
		t[id].sm=t[id].sm+t[id].len*w;
		t[id].vis=t[id].vis+w;
	}else{
		push_down(id);
		int mid=L+R>>1;
		update(l,r,w,L,mid,id<<1);
		update(l,r,w,mid+1,R,id<<1|1);
		t[id].sm=t[id<<1].sm+t[id<<1|1].sm;
	}
}
ll query(int l,int r,int L=1,int R=n,int id=1){
	if(l>R||r<L)return 0;
	if(l<=L&&R<=r)return t[id].sm;
	push_down(id);
	int mid=L+R>>1;
	return query(l,r,L,mid,id<<1)+query(l,r,mid+1,R,id<<1|1);
}
void update_path(int x,int y,int w){ //路径修改
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]){
			update(dfsn[top[x]],dfsn[x],w);
			x=f[top[x]];
		}else {
			update(dfsn[top[y]],dfsn[y],w);
			y=f[top[y]];
		}
	}
	if (dep[x] > dep[y])
        update(dfsn[y], dfsn[x], w);
    else
        update(dfsn[x], dfsn[y], w);
} 
ll query_path(int x,int y){		//路径查询
	ll ans=0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] > dep[top[y]])
        {
            ans =ans+ query(dfsn[top[x]], dfsn[x]);
            x = f[top[x]];
        }
        else
        {
            ans =ans+ query(dfsn[top[y]], dfsn[y]);
            y = f[top[y]];
        }
    }
    if (dep[x] > dep[y])
        ans =ans+ query(dfsn[y], dfsn[x]);
    else
        ans =ans+ query(dfsn[x], dfsn[y]);
    return ans;
}
void update_tree(int x, int w){		//子树修改
    update(dfsn[x], rdfsn[x], w);
}
int query_tree(int x){		//子树查询
    return query(dfsn[x], rdfsn[x]);
}
void solve() {
	cin>>n>>m>>RT;//树的结点个数、操作个数、根节点序号和取模数
	for(int i=1;i<=n;i++)cin>>a[i];//表示各个节点上初始的数值
	int u,v;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs1(RT);//得到每个节点的fa父节点）、sz（子树大小）、dep（深度）、hson（重子节点）
	top[RT]=RT;dfs2(RT);//记录每个点的dfs序,得到每个节点的top（链头） 
	for(int i=1;i<=n;i++)b[dfsn[i]]=a[i];build();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int _ = 1;
	//cin >> _;
	while (_--) {
		solve();
	}
	return 0;
}
/*
*/
