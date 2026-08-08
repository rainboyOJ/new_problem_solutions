// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll A, B, L;

ll gcd_ll(ll x, ll y) {
    while (y != 0) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

void solve() {
    ll ans_a = 0, ans_b = 1;

    for (ll a = 1; a <= L; a++) {
        for (ll b = 1; b <= L; b++) {
            if (gcd_ll(a, b) != 1) {
                continue;
            }
            if (a * B < A * b) {
                continue;
            }
            if (ans_a == 0 || a * ans_b < ans_a * b) {
                ans_a = a;
                ans_b = b;
            }
        }
    }

    cout << ans_a << ' ' << ans_b << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> A >> B >> L;
    solve();

    return 0;
}
