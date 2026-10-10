/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1<<30;
struct Edge{int x,y,z;}; struct Adj{int v,w;};
int find_set(vector<int>&fa,int x){while(fa[x]!=x){fa[x]=fa[fa[x]]; x=fa[x];} return x;}
bool cmp_edge(const Edge&a,const Edge&b){return a.z>b.z;}
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<Edge> edges(m); for(int i=0;i<m;i++) cin>>edges[i].x>>edges[i].y>>edges[i].z; vector<int> fa(n+1); for(int i=1;i<=n;i++) fa[i]=i; vector<vector<Adj> > tree(n+1); sort(edges.begin(),edges.end(),cmp_edge); for(int i=0;i<m;i++){int rx=find_set(fa,edges[i].x), ry=find_set(fa,edges[i].y); if(rx!=ry){fa[rx]=ry; tree[edges[i].x].push_back({edges[i].y,edges[i].z}); tree[edges[i].y].push_back({edges[i].x,edges[i].z});}}
    vector<int> parent(n+1), upw(n+1), depth(n+1), seen(n+1); for(int root=1;root<=n;root++) if(!seen[root]){queue<int> q; q.push(root); seen[root]=1; while(!q.empty()){int u=q.front();q.pop(); for(int i=0;i<(int)tree[u].size();i++){int v=tree[u][i].v,w=tree[u][i].w; if(!seen[v]){seen[v]=1;parent[v]=u;upw[v]=w;depth[v]=depth[u]+1;q.push(v);}}}}
    int LOG=14; vector<vector<int> > up(LOG, vector<int>(n+1)), mn(LOG, vector<int>(n+1)); up[0]=parent; mn[0]=upw; for(int k=1;k<LOG;k++) for(int v=0;v<=n;v++){up[k][v]=up[k-1][up[k-1][v]]; mn[k][v]=min(mn[k-1][v], mn[k-1][up[k-1][v]]);} int qn; cin>>qn; while(qn--){int x,y;cin>>x>>y; if(find_set(fa,x)!=find_set(fa,y)){cout<<-1<<'\n'; continue;} if(depth[x]<depth[y]) swap(x,y); int ans=INF, diff=depth[x]-depth[y]; for(int k=0;k<LOG;k++) if((diff>>k)&1){ans=min(ans,mn[k][x]); x=up[k][x];} if(x==y){cout<<ans<<'\n'; continue;} for(int k=LOG-1;k>=0;k--) if(up[k][x]!=up[k][y]){ans=min(ans,min(mn[k][x],mn[k][y])); x=up[k][x]; y=up[k][y];} cout<<min(ans,min(mn[0][x],mn[0][y]))<<'\n';} return 0;}
