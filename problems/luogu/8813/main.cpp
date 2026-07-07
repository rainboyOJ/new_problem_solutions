#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll LIMIT = 1000000000LL;

ll a, b;

void solve() {
    if (a == 1) {
        cout << 1 << '\n';
        return;
    }

    ll ans = 1;

    // 只要中途超过 1e9，最终答案就已经确定为 -1。
    // 当 a >= 2 时，最多乘约 30 次就会超过 1e9，不会真的循环到 1e9 次。
    for (ll i = 1; i <= b; i++) {
        if (ans > LIMIT / a) {
            cout << -1 << '\n';
            return;
        }
        ans *= a;
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
