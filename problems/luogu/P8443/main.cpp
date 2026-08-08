#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int T;
ll l, r, x;

void solve_one() {
    ll left = l / x;
    ll right = r / x;

    if (left == right) {
        cout << left << '\n';
    } else {
        cout << 1 << '\n';
    }
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
