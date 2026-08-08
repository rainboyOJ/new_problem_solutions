// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Fraction {
    ll num, den;
};

int T, M;
ll a, b, c;

ll gcd_ll(ll x, ll y) {
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    while (y != 0) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

ll abs_ll(ll x) {
    return x >= 0 ? x : -x;
}

Fraction make_fraction(ll num, ll den) {
    if (den < 0) {
        num = -num;
        den = -den;
    }
    ll g = gcd_ll(num, den);
    num /= g;
    den /= g;
    return {num, den};
}

string fraction_to_string(Fraction x) {
    if (x.den == 1) {
        return to_string(x.num);
    }
    return to_string(x.num) + "/" + to_string(x.den);
}

// 暴力枚举最大的平方因子 best^2，使得 best^2 | delta。
void extract_square_part_bruteforce(ll delta, ll &square_part, ll &rest) {
    square_part = 1;
    for (ll d = 1; d * d <= delta; d++) {
        ll sq = d * d;
        if (delta % sq == 0) {
            square_part = d;
        }
    }
    rest = delta / (square_part * square_part);
}

string radical_term_to_string(Fraction coef, ll rest) {
    if (coef.den == 1) {
        if (coef.num == 1) {
            return "sqrt(" + to_string(rest) + ")";
        }
        return to_string(coef.num) + "*sqrt(" + to_string(rest) + ")";
    }

    if (coef.num == 1) {
        return "sqrt(" + to_string(rest) + ")/" + to_string(coef.den);
    }
    return to_string(coef.num) + "*sqrt(" + to_string(rest) + ")/" + to_string(coef.den);
}

string solve_one() {
    ll delta = b * b - 4 * a * c;
    if (delta < 0) {
        return "NO";
    }

    ll sq = (ll) sqrtl((long double) delta);
    while ((sq + 1) * (sq + 1) <= delta) sq++;
    while (sq * sq > delta) sq--;

    if (sq * sq == delta) {
        ll num = -b + (a > 0 ? sq : -sq);
        Fraction ans = make_fraction(num, 2 * a);
        return fraction_to_string(ans);
    }

    Fraction q1 = make_fraction(-b, 2 * a);

    ll square_part, rest;
    extract_square_part_bruteforce(delta, square_part, rest);
    Fraction q2 = make_fraction(square_part, 2 * abs_ll(a));

    string res;
    if (q1.num != 0) {
        res += fraction_to_string(q1);
        res += "+";
    }
    res += radical_term_to_string(q2, rest);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> M;
    while (T--) {
        cin >> a >> b >> c;
        cout << solve_one() << '\n';
    }

    return 0;
}
