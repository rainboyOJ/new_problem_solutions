#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

ll a, b, c;

ll gcd_ll(ll x, ll y) {
    while (y != 0) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

i128 lcm_i128(i128 x, i128 y) {
    ll g = gcd_ll((ll) x, (ll) y);
    return x / g * y;
}

void print_i128(i128 x) {
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }
    string s;
    while (x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << '\n';
}

void solve() {
    i128 ans = lcm_i128(a, b);
    ans = lcm_i128(ans, c);
    print_i128(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c;
    solve();

    return 0;
}
