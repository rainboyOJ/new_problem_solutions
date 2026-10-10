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
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<ll> items(m), cnt(n+1); for(int i=0;i<m;i++){cin>>items[i]; cnt[items[i]]++;} vector<ll>a(n+1),b(n+1),c(n+1),d(n+1); for(int t=2; n-t/2-4*t-1>=1; t+=2){int u=t/2; int am=n-u-4*t-1; vector<ll> p(am+1), pre(am+1); for(int x=1;x<=am;x++){p[x]=cnt[x]*cnt[x+t]; pre[x]=pre[x-1]+p[x];} vector<ll> wsum(am+1); ll suf=0; for(int x=n-u; x>=4*t+2; x--){suf += cnt[x]*cnt[x+u]; int aa=x-4*t-1; if(aa>=1 && aa<=am) wsum[aa]=suf;} for(int aa=1;aa<=am;aa++){a[aa]+=cnt[aa+t]*wsum[aa]; b[aa+t]+=cnt[aa]*wsum[aa];} for(int x=4*t+2;x<=n-u;x++){ll pc=pre[x-4*t-1]; c[x]+=cnt[x+u]*pc; d[x+u]+=cnt[x]*pc;} } for(int i=0;i<m;i++){ll v=items[i]; cout<<a[v]<<' '<<b[v]<<' '<<c[v]<<' '<<d[v]<<'\n';} return 0;}
