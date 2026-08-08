#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

i64 a, b;

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

    cin >> a >> b;

    i64 x0, y0;
    i64 g = exgcd(b, a, x0, y0);

    i64 mod = a / g;

    // y 表示“桶 -> B 杯”需要做多少次。
    // 我们要找最小正整数 y，使得：
    // b * y ≡ g (mod a)
    i64 y = x0 % mod;
    if (y < 0) {
        y += mod;
    }
    if (y == 0) {
        y = mod;
    }

    // x 表示“A 杯 -> 桶”需要做多少次。
    i64 x = (b * y - g) / a;

    cout << g << '\n';
    cout << x << ' ' << y << '\n';

    return 0;
}
