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
const ll INF = (ll)1000000000000000000LL;
int n, rounds_count, current_city; vector<ll> h; vector<int> nearv, secondv; vector<vector<int> > gup; vector<vector<ll> > da, db;
int prefix_sum(vector<int>&bit,int p){int total=0; while(p){total+=bit[p]; p-=p&-p;} return total;}
void mark_bit(vector<int>&bit,int p){int nn=bit.size()-1; while(p<=nn){bit[p]++; p+=p&-p;}}
int kth_bit(vector<int>&bit,int k){int nn=bit.size()-1,pos=0,step=1; while((step<<1)<=nn) step<<=1; while(step){int nxt=pos+step; if(nxt<=nn && bit[nxt]<k){k-=bit[nxt];pos=nxt;} step>>=1;} return pos+1;}
bool cmp_height_idx(int a,int b){ return h[a] < h[b]; }
bool cmp_candidate(int a,int b){ ll da=llabs(h[a]-h[current_city]), db=llabs(h[b]-h[current_city]); if(da!=db) return da<db; return h[a]<h[b]; }
void nearest_two(){ vector<int> order(n); for(int i=0;i<n;i++) order[i]=i+1; sort(order.begin(),order.end(),cmp_height_idx); vector<int> rank(n+1); for(int i=0;i<n;i++) rank[order[i]]=i+1; vector<int> bit(n+1); nearv.assign(n+1,0); secondv.assign(n+1,0); for(int city=n;city>=1;city--){ int r=rank[city]; int less=prefix_sum(bit,r-1); int east=n-city; vector<int> cands; int ks[4]={less,less-1,less+1,less+2}; for(int z=0;z<4;z++){int kk=ks[z]; if(1<=kk && kk<=east) cands.push_back(order[kth_bit(bit,kk)-1]);} current_city=city; sort(cands.begin(),cands.end(),cmp_candidate); if(!cands.empty()){nearv[city]=cands[0]; if(cands.size()>1) secondv[city]=cands[1];} mark_bit(bit,r); } }
ll add_inf(ll x,ll y){ if(x>=INF || y>=INF || x+y>=INF) return INF; return x+y; }
void build_lift(){ rounds_count=max(1, (int)ceil(log2(max(1,n)))); while((1<<rounds_count)<=n-1) rounds_count++; gup.assign(rounds_count, vector<int>(n+1)); da.assign(rounds_count, vector<ll>(n+1,INF)); db.assign(rounds_count, vector<ll>(n+1,INF)); for(int i=1;i<=n;i++){int s=secondv[i]; if(!s) continue; da[0][i]=llabs(h[i]-h[s]); int t=nearv[s]; if(t){db[0][i]=llabs(h[s]-h[t]); gup[0][i]=t;}} for(int k=1;k<rounds_count;k++){ for(int i=0;i<=n;i++){int mid=gup[k-1][i]; gup[k][i]=gup[k-1][mid]; da[k][i]=add_inf(da[k-1][i],da[k-1][mid]); db[k][i]=add_inf(db[k-1][i],db[k-1][mid]); } } }
pair<ll,ll> drive(int start,ll budget){ int city=start; ll remain=budget,total_a=0,total_b=0; for(int k=rounds_count-1;k>=0;k--){ ll cost=da[k][city]+db[k][city]; if(cost<=remain){total_a+=da[k][city]; total_b+=db[k][city]; remain-=cost; city=gup[k][city];}} if(da[0][city]<=remain) total_a+=da[0][city]; return {total_a,total_b}; }
bool better_start(int cand,int best,ll ca,ll cb,ll ba,ll bb){ if(best==0) return true; if(cb==0 && bb==0){ if(h[cand]!=h[best]) return h[cand]>h[best]; return cand<best;} if(cb==0) return false; if(bb==0) return true; __int128 left=(__int128)ca*bb, right=(__int128)ba*cb; if(left!=right) return left<right; if(h[cand]!=h[best]) return h[cand]>h[best]; return cand<best; }
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); if(!(cin>>n)) return 0; h.assign(n+1,0); for(int i=1;i<=n;i++) cin>>h[i]; ll x0; cin>>x0; int m; cin>>m; vector<pair<int,ll> > queries(m); for(int i=0;i<m;i++) cin>>queries[i].first>>queries[i].second; nearest_two(); build_lift(); int ans=0; ll besta=0,bestb=0; for(int st=1;st<=n;st++){pair<ll,ll> p=drive(st,x0); if(better_start(st,ans,p.first,p.second,besta,bestb)){ans=st;besta=p.first;bestb=p.second;}} cout<<ans<<'\n'; for(int i=0;i<m;i++){pair<ll,ll> p=drive(queries[i].first,queries[i].second); cout<<p.first<<' '<<p.second<<'\n';} return 0;}
