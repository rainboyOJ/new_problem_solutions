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
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; int total=n+m; vector<vector<int> > adj(total+1); vector<int> indeg(total+1), level(total+1,1); for(int i=1;i<=m;i++){ int cnt; cin>>cnt; vector<int> stops(cnt); vector<char> is(n+1); for(int j=0;j<cnt;j++){cin>>stops[j]; is[stops[j]]=1;} int hub=n+i; for(int st=stops[0]; st<=stops[cnt-1]; st++){ if(is[st]){adj[hub].push_back(st); indeg[st]++;} else {adj[st].push_back(hub); indeg[hub]++;} } } vector<int> q; for(int u=1;u<=total;u++) if(indeg[u]==0) q.push_back(u); while(!q.empty()){int u=q.back();q.pop_back(); int w=(u<=n); for(int i=0;i<(int)adj[u].size();i++){int v=adj[u][i]; level[v]=max(level[v],level[u]+w); indeg[v]--; if(indeg[v]==0) q.push_back(v);} } int ans=1; for(int i=1;i<=n;i++) ans=max(ans,level[i]); cout<<ans<<'\n'; return 0; }
