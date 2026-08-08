// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int T;
ll l, r, x;

ll gcd_ll(ll a, ll b) {
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void solve_one() {
    ll ans = 0;
    for (ll i = l; i <= r; i++) {
        ll v = i / x;
        if (ans == 0) {
            ans = v;
        } else {
            ans = gcd_ll(ans, v);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> l >> r >> x;
        solve_one();
    }

    return 0;
}
