/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-06 21:12
 * update_at: 2026-11-06 21:12
 */
// brute.cpp：小数据暴力，每次排序求中位数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n; cin >> n;
    vector<ll> v;
    for (ll i = 1; i <= n; i++) {
        ll x; cin >> x; v.push_back(x);
        if (i % 2 == 1) {
            vector<ll> t = v;
            sort(t.begin(), t.end());
            cout << t[(t.size() - 1) / 2] << '\n';
        }
    }
}
