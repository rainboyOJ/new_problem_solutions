#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;
ll cnt[4], price[4];

ll ceil_div(ll a, ll b) {
    return (a + b - 1) / b;
}

void solve() {
    ll ans = (1LL << 60);

    for (int i = 1; i <= 3; i++) {
        ll need = ceil_div(n, cnt[i]);
        ll cost = need * price[i];
        ans = min(ans, cost);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= 3; i++) {
        cin >> cnt[i] >> price[i];
    }
    solve();

    return 0;
}
