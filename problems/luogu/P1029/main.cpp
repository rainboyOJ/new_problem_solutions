#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll x0, yv;

void solve() {
    if (yv % x0 != 0) {
        cout << 0 << '\n';
        return;
    }

    ll n = yv / x0;
    ll ans = 1;

    for (ll p = 2; p * p <= n; p++) {
        if (n % p != 0) {
            continue;
        }
        ans *= 2;
        while (n % p == 0) {
            n /= p;
        }
    }
    if (n > 1) {
        ans *= 2;
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
