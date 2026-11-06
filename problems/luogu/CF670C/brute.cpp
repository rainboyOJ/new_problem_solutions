/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// brute.cpp：小数据暴力，逐个电影数人数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll m; cin >> m;
    vector<ll> b(m), c(m);
    for (ll i = 0; i < m; i++) cin >> b[i];
    for (ll i = 0; i < m; i++) cin >> c[i];
    ll best = 0, ba = -1, bs = -1;
    for (ll i = 0; i < m; i++) {
        ll audio = 0, sub = 0;
        for (ll j = 0; j < n; j++) {
            if (a[j] == b[i]) audio++;
            if (a[j] == c[i]) sub++;
        }
        if (audio > ba || (audio == ba && sub > bs)) { ba = audio; bs = sub; best = i; }
    }
    cout << best + 1 << '\n';
}
