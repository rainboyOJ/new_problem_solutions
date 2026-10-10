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
vector<ll>a,b,c; vector<vector<int> > children; vector<int> depthv, orderv;
ll isqrt_ll(__int128 x){ long double y=(long double)x; ll r=sqrt(y); while((__int128)(r+1)*(r+1)<=x) r++; while((__int128)r*r>x) r--; return r;}
ll ceil_div(ll x,ll y){return (x+y-1)/y;}
ll min_grow_days(ll aa,ll bb,ll cc,ll D){ if(cc==0) return ceil_div(aa,bb); ll q=-cc; if(cc>0 || (bb-1)/q>=D){ ll B=2*bb+cc*(2*D+1); if(cc>0){ __int128 delta=(__int128)B*B-(__int128)8*cc*aa; if(delta<0) return D+1; ll sq=isqrt_ll(delta); ll m=(B-sq+2*cc-1)/(2*cc); while(m>1 && (__int128)B*(m-1)-(__int128)cc*(m-1)*(m-1)>=2*(__int128)aa) m--; while(m<=D && (__int128)B*m-(__int128)cc*m*m<2*(__int128)aa) m++; return m;} ll m=max((isqrt_ll((__int128)B*B+(__int128)8*q*aa)-B+2*q-1)/(2*q),1LL); while(m<=D && (__int128)B*m+(__int128)q*m*m<2*(__int128)aa) m++; return m; }
    ll k=(bb-1)/q, m0=D-k; if(aa<=m0) return aa; if(k==0) return D+1; ll B2=2*bb+cc*(2*k+1); ll nn=max((isqrt_ll((__int128)B2*B2+(__int128)8*q*(aa-m0))-B2+2*q-1)/(2*q),1LL); while(nn<=k && (__int128)B2*nn+(__int128)q*nn*nn<2*(__int128)(aa-m0)) nn++; return nn+m0;}
bool feasible(ll D){int n=a.size(); vector<ll> t(n),mv(n); for(int i=0;i<n;i++){ll mm=min_grow_days(a[i],b[i],c[i],D); if(mm>D) return false; t[i]=D-mm+1;} for(int idx=(int)orderv.size()-1;idx>=0;idx--){int u=orderv[idx]; ll best=t[u]-depthv[u]; for(int j=0;j<(int)children[u].size();j++) if(mv[children[u][j]]<best) best=mv[children[u][j]]; mv[u]=best;} vector<ll> rankv(n); for(int u=0;u<n;u++) rankv[u]=depthv[u]+mv[u]; sort(rankv.begin(),rankv.end()); for(int j=0;j<n;j++) if(rankv[j]<j+1) return false; return true;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; if(!(cin>>n)) return 0; a.resize(n); b.resize(n); c.resize(n); for(int i=0;i<n;i++) cin>>a[i]>>b[i]>>c[i]; vector<vector<int> > g(n); for(int i=0;i<n-1;i++){int u,v;cin>>u>>v;u--;v--;g[u].push_back(v);g[v].push_back(u);} vector<int> parent(n,-1), st; depthv.assign(n,0); children.assign(n,vector<int>()); parent[0]=-2; st.push_back(0); while(!st.empty()){int u=st.back();st.pop_back(); orderv.push_back(u); for(int i=0;i<(int)g[u].size();i++){int v=g[u][i]; if(parent[v]==-1){parent[v]=u; depthv[v]=depthv[u]+1; children[u].push_back(v); st.push_back(v);}}} ll lo=1,hi=1000000000LL; while(lo<hi){ll mid=(lo+hi)/2; if(feasible(mid)) hi=mid; else lo=mid+1;} cout<<lo<<'\n'; return 0;}
