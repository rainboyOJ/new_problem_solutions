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
int n,m; vector<ll> r,d; vector<int> s,t;
bool ok_orders(int k){ vector<ll> diff(n+1); for(int j=0;j<k;j++){ diff[s[j]-1]+=d[j]; diff[t[j]]-=d[j]; } ll cur=0; for(int i=0;i<n;i++){cur+=diff[i]; if(cur>r[i]) return false;} return true; }
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); if(!(cin>>n>>m)) return 0; r.resize(n); for(int i=0;i<n;i++) cin>>r[i]; d.resize(m); s.resize(m); t.resize(m); for(int j=0;j<m;j++) cin>>d[j]>>s[j]>>t[j]; int lo=0,hi=m; while(lo<hi){int mid=(lo+hi+1)/2; if(ok_orders(mid)) lo=mid; else hi=mid-1;} cout << (lo==m?0:-1) << '\n'; if(lo!=m) cout << lo+1 << '\n'; return 0; }
