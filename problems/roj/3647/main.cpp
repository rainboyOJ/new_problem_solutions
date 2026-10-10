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
const ll NEG=-(ll)1000000000000000000LL;
bool check_g(ll g, vector<ll>&xs, vector<ll>&ss, ll d, ll k){ll lo=max(1LL,d-g), hi=d+g; int m=xs.size(); vector<ll> f(m,NEG); f[0]=0; deque<int> dq; int r=-1; for(int i=1;i<m;i++){ll right=xs[i]-lo; while(r+1<m && xs[r+1]<=right){r++; while(!dq.empty() && f[dq.back()]<=f[r]) dq.pop_back(); dq.push_back(r);} ll left=xs[i]-hi; while(!dq.empty() && xs[dq.front()]<left) dq.pop_front(); f[i]=(dq.empty()?NEG:f[dq.front()])+ss[i]; if(f[i]>=k) return true;} return false;}
ll min_coins(vector<ll>&xs,vector<ll>&ss,ll d,ll k){ll pos=0; for(int i=0;i<(int)ss.size();i++) if(ss[i]>0) pos+=ss[i]; if(pos<k) return -1; ll prev=0,maxgap=0; for(int i=0;i<(int)ss.size();i++) if(ss[i]>0){maxgap=max(maxgap,xs[i]-prev); prev=xs[i];} ll lo=0,hi=max(d-1,maxgap-d); while(lo<hi){ll mid=(lo+hi)/2; if(check_g(mid,xs,ss,d,k)) hi=mid; else lo=mid+1;} return lo;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; ll d,k; if(!(cin>>n>>d>>k)) return 0; vector<ll> xs(1,0), ss(1,0); for(int i=0;i<n;i++){ll x,s;cin>>x>>s; xs.push_back(x); ss.push_back(s);} cout<<min_coins(xs,ss,d,k)<<'\n'; return 0;}
