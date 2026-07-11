/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:00
 * update_at: 2026-07-11 19:02
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 205;

int n, q;
ll a[MAXN];
ll b[MAXN];

ll calc_answer() {
    for (int i = 1; i <= n; i++) {
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (ll)i * b[i];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cin >> q;
    while (q--) {
        int idx;
        ll val;
        cin >> idx >> val;

        ll old = a[idx];
        a[idx] = val;
        cout << calc_answer() << '\n';
        a[idx] = old;
    }

    return 0;
}
