#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

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

i64 floor_div(i128 a, i128 b) {
    if (b < 0) {
        a = -a;
        b = -b;
    }
    if (a >= 0) {
        return (i64) (a / b);
    }
    return (i64) (-((-a + b - 1) / b));
}

i64 ceil_div(i128 a, i128 b) {
    if (b < 0) {
        a = -a;
        b = -b;
    }
    if (a >= 0) {
        return (i64) ((a + b - 1) / b);
    }
    return (i64) (-((-a) / b));
}

i64 min_positive_residue(i64 x, i64 mod) {
    i64 r = (x % mod + mod) % mod;
    if (r == 0) {
        r = mod;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        i64 a, b, c;
        cin >> a >> b >> c;

        i64 x0, y0;
        i64 d = exgcd(a, b, x0, y0);

        if (c % d != 0) {
            cout << -1 << '\n';
            continue;
        }

        i64 mul = c / d;
        i64 step_x = b / d;
        i64 step_y = a / d;

        i128 x = (i128) x0 * mul;
        i128 y = (i128) y0 * mul;

        // 通解：
        // x = x0 + k * step_x
        // y = y0 - k * step_y
        i64 kl = ceil_div(1 - x, step_x);
        i64 kr = floor_div(y - 1, step_y);

        if (kl <= kr) {
            i64 cnt = kr - kl + 1;
            i64 xmin = (i64) (x + (i128) kl * step_x);
            i64 xmax = (i64) (x + (i128) kr * step_x);
            i64 ymax = (i64) (y - (i128) kl * step_y);
            i64 ymin = (i64) (y - (i128) kr * step_y);
            cout << cnt << ' ' << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << '\n';
        }
        else {
            i64 xmin = min_positive_residue((i64) x, step_x);
            i64 ymin = min_positive_residue((i64) y, step_y);
            cout << xmin << ' ' << ymin << '\n';
        }
    }

    return 0;
}
