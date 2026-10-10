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
const ll INFLL = (1LL<<60);
int n, tourists, k; vector<ll> d, waitv, alightv, capv, prefixv, aheadv, usedv;
vector<int> next_saturated(){ vector<int> sat(n+2,n+1); for(int j=n;j>=2;j--) sat[j]=(aheadv[j]>=capv[j]?j:sat[j+1]); return sat; }
int pick_edge(vector<int> &sat){ int best=0; ll gain=0; for(int i=1;i<(int)d.size();i++){ if(usedv[i]>=d[i]) continue; int stop=sat[i+1]; if(stop>n) stop=n; ll gi=prefixv[stop]-prefixv[i]; if(gi>gain){best=i; gain=gi;} } return best; }
ll batch_limit(int start, ll budget){ ll gate=INFLL,event=INFLL; for(int j=start+1;j<(int)aheadv.size();j++){ if(aheadv[j]>=capv[j]) break; ll room=capv[j]-aheadv[j]; if(room<=gate) event=min(event, room); gate=min(gate, room); } return min(budget,event); }
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); if(!(cin>>n>>tourists>>k)) return 0; d.assign(n,0); for(int i=1;i<n;i++) cin>>d[i]; waitv.assign(n+1,0); alightv.assign(n+1,0); ll total_t=0; for(int i=0;i<tourists;i++){ll t; int a,b; cin>>t>>a>>b; waitv[a]=max(waitv[a],t); alightv[b]++; total_t += t;} vector<ll> arrive(n+1); for(int i=1;i<n;i++) arrive[i+1]=max(arrive[i],waitv[i])+d[i]; capv.assign(n+1,0); for(int i=2;i<=n;i++) capv[i]=max(arrive[i]-waitv[i],0LL); prefixv.assign(n+1,0); for(int j=2;j<=n;j++) prefixv[j]=prefixv[j-1]+alightv[j]; aheadv.assign(n+1,0); usedv.assign(n+1,0); int remain=k; while(remain>0){ vector<int> sat=next_saturated(); int edge=pick_edge(sat); if(edge==0) break; ll budget=min((ll)remain, d[edge]-usedv[edge]); ll step=batch_limit(edge,budget); usedv[edge]+=step; remain-=step; ll delta=step; for(int j=edge+1;j<=n;j++){ ll room=capv[j]-aheadv[j]; aheadv[j]+=delta; delta=min(delta, room); if(delta<=0) break; } }
    ll base=0,saved=0; for(int j=2;j<=n;j++){ base += arrive[j]*alightv[j]; saved += aheadv[j]*alightv[j]; } cout << base-total_t-saved << '\n'; return 0; }
