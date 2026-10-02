/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 08:45
 * update_at: 2026-10-02 08:45
 */
// main2.cpp：第二种解法。整数二分求 sqrt(delta)，再从大到小枚举平方因子提根号，
// 不分解质因数、不用浮点开方，最后按题面格式输出较大实根。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

// 把分数约成最简形式，并保证分母为正。
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

// 整数开方：返回最大的 s 满足 s * s <= x（x >= 0）。
// 二分求解，避免 (long double) sqrt 舍入带来的边界误差。
ll isqrt(ll x) {
    ll left = 0;
    ll right = 1;
    while (right * right <= x) {
        right *= 2;
    }
    ll answer = 0;
    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (mid * mid <= x) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return answer;
}

// 从大到小枚举 s，第一个满足 s * s 整除 delta 的 s 就是最大平方因子，
// 于是 delta = s * s * r，且 r 中不再含平方因子。
// delta = b*b - 4ac <= 10^6 + 4 * 10^6 = 5 * 10^6，所以 s 最多枚举到 2237 左右。
ll max_square_factor(ll delta) {
    for (ll s = isqrt(delta); s >= 1; s--) {
        if (delta % (s * s) == 0) {
            return s;
        }
    }
    return 1;
}

// 根号项的四种输出格式：1、整数、1/q、c/q（约分后 c、q 互质）。
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

    ll sq = isqrt(delta);
    // 判别式是完全平方数时，较大根一定是有理数，直接约分输出。
    if (sq * sq == delta) {
        ll num = -b + (a > 0 ? sq : -sq); // a < 0 时分母为负，取 -sq 让根号项仍为正
        return fraction_to_string(make_fraction(num, 2 * a));
    }

    // 较大根统一写成 -b/(2a) + sqrt(delta)/(2|a|)，这样根号项系数恒为正，
    // 正好满足题目要求的 q2 > 0。
    Fraction q1 = make_fraction(-b, 2 * a);

    ll s = max_square_factor(delta); // delta = s * s * r
    Fraction q2 = make_fraction(s, 2 * (a > 0 ? a : -a));

    string res;
    if (q1.num != 0) { // q1 = 0 时按题面跳过有理数部分，直接写根号项
        res += fraction_to_string(q1);
        res += "+";
    }
    res += radical_term_to_string(q2, delta / (s * s));
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
