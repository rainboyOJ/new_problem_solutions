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

int x1_, y1_, x2_, y2_;
int n;
vector<pair<ll, ll> > pairs;   // (d1, d2) 距离平方

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> x1_ >> y1_ >> x2_ >> y2_;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        ll d1 = (x - x1_) * (x - x1_) + (y - y1_) * (y - y1_);
        ll d2 = (x - x2_) * (x - x2_) + (y - y2_) * (y - y2_);
        pairs.push_back(make_pair(d1, d2));
    }
    sort(pairs.begin(), pairs.end());

    // suf[i]：第 i 颗及以后全交给 2 号系统所需的 d2 后缀最大值
    vector<ll> suf(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
        suf[i] = max(pairs[i].second, suf[i + 1]);

    ll ans = 1LL << 62;
    for (int k = 0; k <= n; k++) {
        ll r1 = (k ? pairs[k - 1].first : 0);
        ll cand = r1 + suf[k];
        if (cand < ans) ans = cand;
    }
    cout << ans << "\n";
    return 0;
}
