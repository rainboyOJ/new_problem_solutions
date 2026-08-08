// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll LIMIT = 1000000000LL;

ll a, b;

void solve() {
    ll ans = 1;
    for (ll i = 1; i <= b; i++) {
        if (ans > LIMIT / a) {
            cout << -1 << '\n';
            return;
        }
        ans *= a;
        if (ans > LIMIT) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    solve();

    return 0;
}
