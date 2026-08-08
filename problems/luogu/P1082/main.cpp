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

i64 inverse(i64 a, i64 mod) {
    i64 x, y;
    i64 d = exgcd(a, mod, x, y);
    if (d != 1) {
        return -1;
    }
    return (x % mod + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b;
    cin >> a >> b;

    cout << inverse(a, b) << '\n';
    return 0;
}
