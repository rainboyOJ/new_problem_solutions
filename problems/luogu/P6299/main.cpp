#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

struct GaussInt {
    i128 x, y; // x + yi
};

struct Answer {
    i128 p, q, r, s;
};

GaussInt operator + (const GaussInt &a, const GaussInt &b) {
    return {a.x + b.x, a.y + b.y};
}

GaussInt operator - (const GaussInt &a, const GaussInt &b) {
    return {a.x - b.x, a.y - b.y};
}

GaussInt operator * (const GaussInt &a, const GaussInt &b) {
    return {
        a.x * b.x - a.y * b.y,
        a.x * b.y + a.y * b.x
    };
}

bool is_zero(const GaussInt &a) {
    return a.x == 0 && a.y == 0;
}

i128 norm(const GaussInt &a) {
    return a.x * a.x + a.y * a.y;
}

string to_string_i128(i128 x) {
    if (x == 0) {
        return "0";
    }

    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }

    string s;
    while (x > 0) {
        int digit = (int) (x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) {
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return s;
}

// 把 a / b 四舍五入到最近的整数。
i128 round_div(i128 a, i128 b) {
    if (a >= 0) {
        return (a + b / 2) / b;
    }
    return -((-a + b / 2) / b);
}

// 高斯整数带余除法：a = bq + r，且 r 的范数足够小。
GaussInt gauss_div(const GaussInt &a, const GaussInt &b) {
    i128 den = norm(b);
    i128 real_up = a.x * b.x + a.y * b.y;
    i128 imag_up = a.y * b.x - a.x * b.y;
    return {
        round_div(real_up, den),
        round_div(imag_up, den)
    };
}

// 返回 gcd(a, b)，并求出 ax + by = gcd(a, b) 的一组贝祖系数。
GaussInt exgcd(const GaussInt &a, const GaussInt &b, GaussInt &x, GaussInt &y) {
    if (is_zero(b)) {
        x = {1, 0};
        y = {0, 0};
        return a;
    }

    GaussInt q = gauss_div(a, b);
    GaussInt r = a - q * b;

    GaussInt x1, y1;
    GaussInt g = exgcd(b, r, x1, y1);

    x = y1;
    y = x1 - q * y1;
    return g;
}

GaussInt mul_unit(const GaussInt &a, int type) {
    if (type == 0) return a;             // 1
    if (type == 1) return {-a.x, -a.y}; // -1
    if (type == 2) return {-a.y, a.x};  // i
    return {a.y, -a.x};                 // -i
}

Answer decode_answer(const GaussInt &u, const GaussInt &v) {
    // 原式可以写成：
    // M = |(a+bi)(p-qi) + (c+di)(r+si)|^2
    return {u.x, -u.y, v.x, v.y};
}

bool better_answer(const Answer &a, const Answer &b) {
    if (a.p != b.p) return a.p > b.p;
    if (a.q != b.q) return a.q > b.q;
    if (a.r != b.r) return a.r > b.r;
    return a.s > b.s;
}

Answer normalize_answer(const GaussInt &u, const GaussInt &v) {
    bool first = true;
    Answer best = {0, 0, 0, 0};

    // 同乘一个单位元 ±1、±i，不会改变最小范数。
    // 为了让本地样例输出稳定，这里固定选字典序最大的那一组。
    for (int type = 0; type < 4; type++) {
        GaussInt nu = mul_unit(u, type);
        GaussInt nv = mul_unit(v, type);
        Answer cur = decode_answer(nu, nv);
        if (first || better_answer(cur, best)) {
            first = false;
            best = cur;
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b, c, d;
    cin >> a >> b >> c >> d;

    GaussInt A = {(i128) a, (i128) b};
    GaussInt B = {(i128) c, (i128) d};

    GaussInt u, v;
    GaussInt g = exgcd(A, B, u, v);

    Answer ans = normalize_answer(u, v);
    i128 M = norm(g);

    cout << to_string_i128(ans.p) << ' '
         << to_string_i128(ans.q) << ' '
         << to_string_i128(ans.r) << ' '
         << to_string_i128(ans.s) << ' '
         << to_string_i128(M) << '\n';

    return 0;
}
