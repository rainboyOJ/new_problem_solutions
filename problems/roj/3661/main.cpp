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
vector<pair<int,int> > find_cycle(vector<vector<int> >&adj){int n=adj.size()-1; vector<int> parent(n+1), seen(n+1); seen[1]=1; vector<pair<int,int> > st; st.push_back({1,0}); while(!st.empty()){int u=st.back().first, i=st.back().second; if(i>=(int)adj[u].size()){st.pop_back(); continue;} st.back().second=i+1; int v=adj[u][i]; if(v==parent[u]) continue; if(seen[v]){vector<int> path; path.push_back(u); int x=u; while(x!=v){x=parent[x]; path.push_back(x);} vector<pair<int,int> > res; for(int j=0;j+1<(int)path.size();j++) res.push_back({path[j],path[j+1]}); res.push_back({u,v}); return res;} seen[v]=1; parent[v]=u; st.push_back({v,0});} return vector<pair<int,int> >();}
vector<int> tree_walk(vector<vector<int> >&adj,pair<int,int> cut){int n=adj.size()-1; int su=cut.first,sv=cut.second; vector<int> vis(n+1), seq, path(n+1), step(n+1); vis[1]=1; seq.push_back(1); path[0]=1; int top=1; while(top){int u=path[top-1]; int i=step[top-1]; if(i==(int)adj[u].size()){top--; continue;} step[top-1]=i+1; int v=adj[u][i]; if((u==su&&v==sv)||(u==sv&&v==su)) continue; if(vis[v]) continue; vis[v]=1; seq.push_back(v); path[top]=v; step[top]=0; top++;} return seq;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<vector<int> > adj(n+1); for(int i=0;i<m;i++){int u,v;cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u);} for(int i=1;i<=n;i++) sort(adj[i].begin(),adj[i].end()); vector<pair<int,int> > cuts; if(m==n) cuts=find_cycle(adj); else cuts.push_back({0,0}); vector<int> best=tree_walk(adj,cuts[0]); for(int i=1;i<(int)cuts.size();i++){vector<int> seq=tree_walk(adj,cuts[i]); if(seq<best) best=seq;} for(int i=0;i<(int)best.size();i++){if(i) cout<<' '; cout<<best[i];} cout<<'\n'; return 0;}
