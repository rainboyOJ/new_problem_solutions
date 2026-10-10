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
vector<ll> DIST, WTOP; vector<vector<int> > UP, CH; vector<int> ORDER, TOP, RC, ARMY; vector<ll> NEG_D; int LOGN, M;
int lift_node(int v, ll x){ ll threshold=DIST[v]-x; int u=v; for(int j=LOGN-1;j>=0;j--){int a=UP[j][u]; if(a && DIST[a]>=threshold) u=a;} return u; }
vector<char> subtree_covered(vector<char> &vis){ vector<char> cov(DIST.size()); for(int idx=(int)ORDER.size()-1; idx>=0; idx--){int u=ORDER[idx]; if(vis[u]){cov[u]=1; continue;} if(!CH[u].empty()){char ok=1; for(int i=0;i<(int)CH[u].size();i++) if(!cov[CH[u][i]]){ok=0;break;} cov[u]=ok;}} return cov; }
bool feasible_time(ll x){ vector<char> vis(DIST.size()); int split=lower_bound(NEG_D.begin(),NEG_D.end(),-x)-NEG_D.begin(); for(int i=0;i<split;i++) vis[lift_node(ARMY[i],x)]=1; vector<char> cov=subtree_covered(vis); vector<ll> pool; for(int i=split;i<M;i++){int v=ARMY[i]; ll rest=x-DIST[v]; int son=TOP[v]; if(!cov[son] && rest<WTOP[son]) cov[son]=1; else pool.push_back(rest);} int j=0; for(int idx=0;idx<(int)RC.size();idx++){int c=RC[idx]; if(cov[c]) continue; ll w=WTOP[c]; while(j<(int)pool.size() && pool[j]<w) j++; if(j==(int)pool.size()) return false; j++;} return true; }
struct Edge{int v; ll w;};
bool cmp_army(int a,int b){ return DIST[a] > DIST[b]; }
bool cmp_root_child(int a,int b){ return WTOP[a] < WTOP[b]; }
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); int n; if(!(cin>>n)) return 0; vector<vector<Edge> > adj(n+1); ll total=0; for(int i=0;i<n-1;i++){int u,v;ll w;cin>>u>>v>>w; adj[u].push_back({v,w}); adj[v].push_back({u,w}); total+=w;} DIST.assign(n+1,0); CH.assign(n+1,vector<int>()); TOP.assign(n+1,0); WTOP.assign(n+1,0); vector<int> fa(n+1); vector<char> seen(n+1); queue<int> q; seen[1]=1; q.push(1); while(!q.empty()){int u=q.front(); q.pop(); for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i].v; ll w=adj[u][i].w; if(seen[v]) continue; seen[v]=1; DIST[v]=DIST[u]+w; CH[u].push_back(v); fa[v]=u; TOP[v]=(u==1?v:TOP[u]); if(u==1) WTOP[v]=w; ORDER.push_back(v); q.push(v);}} LOGN=1; while((1<<LOGN)<=n) LOGN++; UP.assign(LOGN, vector<int>(n+1)); for(int v=0;v<=n;v++) UP[0][v]=fa[v]; for(int j=1;j<LOGN;j++) for(int v=0;v<=n;v++) UP[j][v]=UP[j-1][UP[j-1][v]]; cin>>M; ARMY.resize(M); for(int i=0;i<M;i++) cin>>ARMY[i]; sort(ARMY.begin(),ARMY.end(),cmp_army); NEG_D.resize(M); for(int i=0;i<M;i++) NEG_D[i]=-DIST[ARMY[i]]; RC=CH[1]; sort(RC.begin(),RC.end(),cmp_root_child); if(M<(int)CH[1].size()){cout<<-1<<'\n';return 0;} ll lo=0,hi=total; while(lo<hi){ll mid=(lo+hi)/2; if(feasible_time(mid)) hi=mid; else lo=mid+1;} cout<<lo<<'\n'; return 0; }
