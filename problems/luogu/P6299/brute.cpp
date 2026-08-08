#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128_t;

const int LIM = 12;

struct Answer {
    i64 p, q, r, s;
    i128 m;
};

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

i128 calc_value(i64 a, i64 b, i64 c, i64 d, i64 p, i64 q, i64 r, i64 s) {
    // M = |(a+bi)(p-qi) + (c+di)(r+si)|^2
    i128 real_part = (i128) a * p + (i128) b * q + (i128) c * r - (i128) d * s;
    i128 imag_part = (i128) b * p - (i128) a * q + (i128) c * s + (i128) d * r;
    return real_part * real_part + imag_part * imag_part;
}

bool better_answer(const Answer &a, const Answer &b) {
    if (a.m != b.m) return a.m < b.m;
    if (a.p != b.p) return a.p > b.p;
    if (a.q != b.q) return a.q > b.q;
    if (a.r != b.r) return a.r > b.r;
    return a.s > b.s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b, c, d;
    cin >> a >> b >> c >> d;

    Answer best = {0, 0, 0, 0, -1};
    bool found = false;

    // 只用于小数据验证：直接枚举 p, q, r, s。
    for (i64 p = -LIM; p <= LIM; p++) {
        for (i64 q = -LIM; q <= LIM; q++) {
            for (i64 r = -LIM; r <= LIM; r++) {
                for (i64 s = -LIM; s <= LIM; s++) {
                    i128 now = calc_value(a, b, c, d, p, q, r, s);
                    if (now == 0) {
                        continue;
                    }

                    Answer cur = {p, q, r, s, now};
                    if (!found || better_answer(cur, best)) {
                        found = true;
                        best = cur;
                    }
                }
            }
        }
    }

    cout << best.p << ' '
         << best.q << ' '
         << best.r << ' '
         << best.s << ' '
         << to_string_i128(best.m) << '\n';

    return 0;
}
