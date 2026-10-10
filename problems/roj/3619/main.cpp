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
const int MOD=10007;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; if(!(cin>>n)) return 0; vector<vector<int> > adj(n+1); for(int i=0;i<n-1;i++){int u,v;cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u);} vector<ll>w(n+1); for(int i=1;i<=n;i++) cin>>w[i]; ll total=0,best=0; for(int u=1;u<=n;u++){ ll s=0,sq=0,m1=0,m2=0; for(int i=0;i<(int)adj[u].size();i++){ll x=w[adj[u][i]]; s+=x; sq+=x*x; if(x>m1){m2=m1;m1=x;} else if(x>m2) m2=x;} total += s*s - sq; best=max(best,m1*m2);} cout<<best<<' '<<total%MOD<<'\n'; return 0;}
