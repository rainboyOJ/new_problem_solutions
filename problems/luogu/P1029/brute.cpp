// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll x0, yv;

ll gcd_ll(ll a, ll b) {
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void solve() {
    if (yv % x0 != 0) {
        cout << 0 << '\n';
        return;
    }

    ll n = yv / x0;
    ll ans = 0;

    for (ll a = 1; a * a <= n; a++) {
        if (n % a != 0) {
            continue;
        }
        ll b = n / a;
        if (gcd_ll(a, b) == 1) {
            if (a == b) {
                ans += 1;
            } else {
                ans += 2;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x0 >> yv;
    solve();

    return 0;
}
