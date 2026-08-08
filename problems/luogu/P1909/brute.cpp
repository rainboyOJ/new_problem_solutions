// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;
ll cnt[4], price[4];

void solve() {
    ll ans = (1LL << 60);

    for (int i = 1; i <= 3; i++) {
        ll pack = 0;
        while (pack * cnt[i] < n) {
            pack++;
        }
        ans = min(ans, pack * price[i]);
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
