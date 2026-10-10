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
struct Edge{int v; ll w;};
int max_pairs(vector<ll> rest,ll limit){int i=0,j=(int)rest.size()-1,pairs=0; while(i<j){if(rest[i]+rest[j]>=limit){pairs++;i++;j--;} else i++;} return pairs;}
pair<int,ll> pair_chains(vector<ll> rests,ll limit){int singles=0; vector<ll> rest; for(int i=0;i<(int)rests.size();i++){if(rests[i]>=limit) singles++; else rest.push_back(rests[i]);} sort(rest.begin(),rest.end()); int p=max_pairs(rest,limit); ll leftover=0; int lo=0,hi=(int)rest.size()-1; while(lo<hi){int mid=(lo+hi+1)/2; vector<ll> keep; for(int i=0;i<(int)rest.size();i++) if(i!=mid) keep.push_back(rest[i]); if(max_pairs(keep,limit)>=p) lo=mid; else hi=mid-1;} if(p*2<(int)rest.size() && !rest.empty()) leftover=rest[lo]; return {singles+p,leftover};}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<vector<Edge> > adj(n+1); ll total_len=0; for(int i=0;i<n-1;i++){int a,b; ll l;cin>>a>>b>>l; adj[a].push_back({b,l}); adj[b].push_back({a,l}); total_len+=l;} vector<int> parent(n+1), order; order.push_back(1); for(int idx=0;idx<(int)order.size();idx++){int u=order[idx]; for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i].v; if(v!=parent[u]){parent[v]=u; order.push_back(v);}}} ll lo=1,hi=total_len; while(lo<hi){ll mid=(lo+hi+1)/2; int total=0; vector<ll> up(n+1); for(int idx=(int)order.size()-1;idx>=0;idx--){int u=order[idx]; vector<ll> rests; for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i].v; if(v!=parent[u]) rests.push_back(up[v]+adj[u][i].w);} pair<int,ll> pr=pair_chains(rests,mid); total+=pr.first; up[u]=pr.second;} if(total>=m) lo=mid; else hi=mid-1;} cout<<lo<<'\n'; return 0;}
