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
struct Ore { ll w, v; };
struct Query { int l, r; };
vector<Ore> ores; vector<Query> qs; ll target; int n, m;
ll evaluate_value(ll limit) {
    vector<ll> cnt(n + 1), sv(n + 1);
    for (int i = 1; i <= n; i++) {
        cnt[i] = cnt[i - 1] + (ores[i - 1].w >= limit);
        sv[i] = sv[i - 1] + (ores[i - 1].w >= limit ? ores[i - 1].v : 0);
    }
    ll total = 0;
    for (int i = 0; i < m; i++) total += (cnt[qs[i].r] - cnt[qs[i].l - 1]) * (sv[qs[i].r] - sv[qs[i].l - 1]);
    return total;
}
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); if(!(cin>>n>>m>>target)) return 0; ores.resize(n); qs.resize(m); ll mx=0; for(int i=0;i<n;i++){cin>>ores[i].w>>ores[i].v; mx=max(mx,ores[i].w);} for(int i=0;i<m;i++) cin>>qs[i].l>>qs[i].r; ll lo=1,hi=mx+2; while(lo<hi){ll mid=(lo+hi)/2; if(evaluate_value(mid)>target) lo=mid+1; else hi=mid;} ll a=evaluate_value(lo), b=evaluate_value(lo-1); cout << min(llabs(a-target), llabs(b-target)) << '\n'; return 0; }
