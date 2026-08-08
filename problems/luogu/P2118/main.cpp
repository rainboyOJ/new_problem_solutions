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

    for (ll b = 1; b <= L; b++) {
        ll a = (A * b + B - 1) / B;  // ceil(A*b / B)

        while (a <= L && gcd_ll(a, b) != 1) {
            a++;
        }
        if (a > L) {
            continue;
        }

        if (ans_a == 0 || a * ans_b < ans_a * b) {
            ans_a = a;
            ans_b = b;
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
