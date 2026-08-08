#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

const i64 INF64 = (1LL << 60);

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

bool add_constraint(i64 x0, i64 step, i64 L, i64 R, i64 &kl, i64 &kr) {
    if (L > R) {
        return false;
    }

    if (step == 0) {
        return L <= x0 && x0 <= R;
    }

    i64 l, r;
    if (step > 0) {
        l = ceil_div((i128) L - x0, step);
        r = floor_div((i128) R - x0, step);
    }
    else {
        l = ceil_div((i128) R - x0, step);
        r = floor_div((i128) L - x0, step);
    }

    kl = max(kl, l);
    kr = min(kr, r);
    return kl <= kr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;

    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }

    i64 rhs = -c;

    if (a == 0 && b == 0) {
        if (rhs == 0) {
            cout << (i64) ((i128) (x2 - x1 + 1) * (y2 - y1 + 1)) << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        return 0;
    }

    if (a == 0) {
        if (rhs % b != 0) {
            cout << 0 << '\n';
            return 0;
        }
        i64 y = rhs / b;
        if (y1 <= y && y <= y2) {
            cout << (x2 - x1 + 1) << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        return 0;
    }

    if (b == 0) {
        if (rhs % a != 0) {
            cout << 0 << '\n';
            return 0;
        }
        i64 x = rhs / a;
        if (x1 <= x && x <= x2) {
            cout << (y2 - y1 + 1) << '\n';
        }
        else {
            cout << 0 << '\n';
        }
        return 0;
    }

    i64 x0, y0;
    i64 d = exgcd(llabs(a), llabs(b), x0, y0);

    if (a < 0) {
        x0 = -x0;
    }
    if (b < 0) {
        y0 = -y0;
    }

    if (rhs % d != 0) {
        cout << 0 << '\n';
        return 0;
    }

    i64 mul = rhs / d;
    i64 base_x = (i128) x0 * mul;
    i64 base_y = (i128) y0 * mul;
    i64 step_x = b / d;
    i64 step_y = -a / d;

    i64 kl = -INF64, kr = INF64;
    if (!add_constraint(base_x, step_x, x1, x2, kl, kr)) {
        cout << 0 << '\n';
        return 0;
    }
    if (!add_constraint(base_y, step_y, y1, y2, kl, kr)) {
        cout << 0 << '\n';
        return 0;
    }

    cout << (kr - kl + 1) << '\n';
    return 0;
}
