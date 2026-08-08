#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;

void solve() {
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            cout << n / d << '\n';
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
