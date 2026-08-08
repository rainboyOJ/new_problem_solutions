#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;

    i64 a = m - n;
    i64 c = y - x;

    if (a < 0) {
        a = -a;
        c = -c;
    }

    i64 p, q;
    i64 d = exgcd(a, L, p, q);

    if (c % d != 0) {
        cout << "Impossible\n";
        return 0;
    }

    i64 mod = L / d;
    i64 ans = (__int128) p * (c / d) % mod;
    ans = (ans % mod + mod) % mod;

    cout << ans << '\n';
    return 0;
}
