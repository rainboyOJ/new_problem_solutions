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
int find_set(vector<int>&fa,int x){while(fa[x]!=x){fa[x]=fa[fa[x]];x=fa[x];}return x;}
int count_in_bucket(map<int, vector<int> > &buckets,int key,int lo,int hi){auto it=buckets.find(key); if(it==buckets.end()) return 0; vector<int>&v=it->second; return upper_bound(v.begin(),v.end(),hi)-lower_bound(v.begin(),v.end(),lo);}
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<vector<int> > adj(n+1); for(int i=0;i<n-1;i++){int u,v;cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u);} vector<int> weight(n+1); for(int i=1;i<=n;i++) cin>>weight[i]; vector<int>s(m),t(m),lca(m); vector<vector<int> > at_s(n+1), at_t(n+1); for(int i=0;i<m;i++){cin>>s[i]>>t[i]; at_s[s[i]].push_back(i); at_t[t[i]].push_back(i);} vector<int> parent(n+1), depth(n+1), anc(n+1), order; vector<char> vis(n+1); for(int i=0;i<=n;i++) anc[i]=i; vector<int> it(n+1); vis[1]=1; order.push_back(1); for(int z=0;z<(int)at_s[1].size();z++){int i=at_s[1][z]; if(vis[t[i]]) lca[i]=find_set(anc,t[i]);} for(int z=0;z<(int)at_t[1].size();z++){int i=at_t[1][z]; if(vis[s[i]]) lca[i]=find_set(anc,s[i]);}
    vector<int> st; st.push_back(1); while(!st.empty()){int u=st.back(); if(it[u]<(int)adj[u].size()){int v=adj[u][it[u]++]; if(!vis[v]){vis[v]=1; parent[v]=u; depth[v]=depth[u]+1; order.push_back(v); for(int z=0;z<(int)at_s[v].size();z++){int i=at_s[v][z]; if(vis[t[i]]) lca[i]=find_set(anc,t[i]);} for(int z=0;z<(int)at_t[v].size();z++){int i=at_t[v][z]; if(vis[s[i]]) lca[i]=find_set(anc,s[i]);} st.push_back(v);}} else {st.pop_back(); if(u!=1) anc[find_set(anc,u)]=parent[u];}}
    vector<int> tin(n+1), sz(n+1,1); for(int i=0;i<(int)order.size();i++) tin[order[i]]=i; for(int i=(int)order.size()-1;i>=0;i--){int u=order[i]; if(u!=1) sz[parent[u]]+=sz[u];}
    map<int, vector<int> > up_add,up_sub,down_add,down_sub; for(int i=0;i<m;i++){int d0=depth[s[i]]; int k=d0-2*depth[lca[i]]; up_add[d0].push_back(tin[s[i]]); down_add[k].push_back(tin[t[i]]); if(parent[lca[i]]) up_sub[d0].push_back(tin[parent[lca[i]]]); down_sub[k].push_back(tin[lca[i]]);} for(map<int,vector<int> >::iterator itb=up_add.begin();itb!=up_add.end();++itb) sort(itb->second.begin(),itb->second.end()); for(map<int,vector<int> >::iterator itb=up_sub.begin();itb!=up_sub.end();++itb) sort(itb->second.begin(),itb->second.end()); for(map<int,vector<int> >::iterator itb=down_add.begin();itb!=down_add.end();++itb) sort(itb->second.begin(),itb->second.end()); for(map<int,vector<int> >::iterator itb=down_sub.begin();itb!=down_sub.end();++itb) sort(itb->second.begin(),itb->second.end());
    for(int u=1;u<=n;u++){int lo=tin[u], hi=lo+sz[u]-1, du=depth[u]; int ans=count_in_bucket(up_add,du+weight[u],lo,hi)+count_in_bucket(down_add,weight[u]-du,lo,hi)-count_in_bucket(up_sub,du+weight[u],lo,hi)-count_in_bucket(down_sub,weight[u]-du,lo,hi); if(u>1) cout<<' '; cout<<ans;} cout<<'\n'; return 0;}
