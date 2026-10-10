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
const ll INF = (1LL<<60), BIG = 1000000000LL;
struct Edge{int v; ll d;};
struct State{ll f, dist; int u; string mask; bool operator<(const State& o) const { if(f!=o.f) return f>o.f; return dist>o.dist; }};
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); int n,k,m,s,t; if(!(cin>>n>>k>>m>>s>>t)) return 0; vector<int> culture(n+1); for(int i=1;i<=n;i++) cin>>culture[i]; vector<vector<int> > reject(k+1, vector<int>(k+1)); for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) cin>>reject[i][j]; vector<vector<Edge> > adj(n+1); for(int i=0;i<m;i++){int u,v;ll d;cin>>u>>v>>d; adj[u].push_back({v,d}); adj[v].push_back({u,d});}
    vector<char> seen(n+1); queue<int> bfs; seen[s]=1; bfs.push(s); while(!bfs.empty()){int u=bfs.front();bfs.pop(); for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i].v; if(!seen[v]){seen[v]=1;bfs.push(v);}}} if(!seen[t]){cout<<-1<<'\n';return 0;}
    bool last=false; for(int w=1;w<=n;w++) if(seen[w]&&culture[w]!=culture[t]&&!reject[culture[w]][culture[t]]) for(int i=0;i<(int)adj[w].size();i++) if(adj[w][i].v==t) last=true; if(!last){cout<<-1<<'\n';return 0;}
    vector<ll> h(n+1,BIG); priority_queue<pair<ll,int>, vector<pair<ll,int> >, greater<pair<ll,int> > > pq; h[t]=0; pq.push({0,t}); while(!pq.empty()){pair<ll,int> cur=pq.top();pq.pop(); ll du=cur.first; int u=cur.second; if(du>h[u]) continue; for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i].v; ll nd=du+adj[u][i].d; if(nd<h[v]){h[v]=nd;pq.push({nd,v});}}}
    map<pair<int,string>, ll> best; priority_queue<State> heap; string sm(k+1,'0'); sm[culture[s]]='1'; best[{s,sm}]=0; heap.push({h[s],0,s,sm}); while(!heap.empty()){State cur=heap.top(); heap.pop(); int u=cur.u; string mask=cur.mask; ll dist=cur.dist; pair<int,string> key={u,mask}; if(best[key]<dist) continue; if(u==t){cout<<dist<<'\n';return 0;} for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i].v; int c=culture[v]; if(mask[c]=='1') continue; if(reject[culture[u]][c]) continue; string nmask=mask; nmask[c]='1'; ll nd=dist+adj[u][i].d; pair<int,string> nk={v,nmask}; if(!best.count(nk)||nd<best[nk]){best[nk]=nd; heap.push({nd+h[v],nd,v,nmask});}} }
    cout<<-1<<'\n'; return 0; }
