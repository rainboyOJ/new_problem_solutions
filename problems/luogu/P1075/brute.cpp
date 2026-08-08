// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;

void solve() {
    for (ll d = 2; d < n; d++) {
        if (n % d == 0) {
            ll other = n / d;
            if (d > other) {
                cout << d << '\n';
            } else {
                cout << other << '\n';
            }
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    solve();

    return 0;
}
