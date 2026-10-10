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
struct Edge{int v,w;};
int lca_node(int u,int v,vector<int>&depth,vector<vector<int> >&up){ if(depth[u]<depth[v]) swap(u,v); int diff=depth[u]-depth[v]; for(int k=0;k<(int)up.size();k++) if((diff>>k)&1) u=up[k][u]; if(u==v) return u; for(int k=(int)up.size()-1;k>=0;k--) if(up[k][u]!=up[k][v]){u=up[k][u]; v=up[k][v];} return up[0][u]; }
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<vector<Edge> > g(n+1); for(int i=0;i<n-1;i++){int a,b,t;cin>>a>>b>>t; g[a].push_back({b,t}); g[b].push_back({a,t});} vector<int> parent(n+1),depth(n+1),wpar(n+1),order; vector<ll> dist(n+1); vector<int> stack; stack.push_back(1); while(!stack.empty()){int u=stack.back();stack.pop_back(); order.push_back(u); for(int i=0;i<(int)g[u].size();i++){int v=g[u][i].v,w=g[u][i].w; if(v!=parent[u]){parent[v]=u; depth[v]=depth[u]+1; dist[v]=dist[u]+w; wpar[v]=w; stack.push_back(v);}}} int LOG=1; while((1<<LOG)<=n) LOG++; vector<vector<int> > up(LOG, vector<int>(n+1)); up[0]=parent; for(int k=1;k<LOG;k++) for(int v=0;v<=n;v++) up[k][v]=up[k-1][up[k-1][v]]; vector<int> pu(m),pv(m),pl(m); vector<ll> lens(m); for(int j=0;j<m;j++){int u,v;cin>>u>>v; int w=lca_node(u,v,depth,up); pu[j]=u; pv[j]=v; pl[j]=w; lens[j]=dist[u]+dist[v]-2*dist[w];} vector<int> diff(n+1); ll max_len=0; for(int i=0;i<m;i++) max_len=max(max_len,lens[i]); int maxw=0; for(int i=1;i<=n;i++) maxw=max(maxw,wpar[i]); ll lo=max(0LL,max_len-maxw), hi=max_len; while(lo<hi){ll limit=(lo+hi)/2; int over=0; ll longest=0; for(int j=0;j<m;j++) if(lens[j]>limit){over++; longest=max(longest,lens[j]); diff[pu[j]]++; diff[pv[j]]++; diff[pl[j]]-=2;} bool ok; if(over==0) ok=true; else {ll need=longest-limit; int best=0; for(int idx=(int)order.size()-1; idx>=0; idx--){int v=order[idx], d=diff[v]; diff[v]=0; if(parent[v]){diff[parent[v]]+=d; if(d==over && wpar[v]>best) best=wpar[v];}} ok=best>=need;} if(ok) hi=limit; else lo=limit+1; } cout<<lo<<'\n'; return 0;}
