/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:59
 * update_at: 2026-10-05 01:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

typedef long long ll;

ll n;
ll a[MAXN]; // 第 i 条曲线的二次项系数
ll b[MAXN]; // 第 i 条曲线的一次项系数
ll c[MAXN]; // 第 i 条曲线的常数项

// 上包络 F(x) = max_i (a_i * x^2 + b_i * x + c_i)
double envelope(double x) {
    double best = -1e18;
    for (ll i = 0; i < n; i++) {
        double value = a[i] * x * x + b[i] * x + c[i];
        if (value > best) {
            best = value;
        }
    }
    return best;
}

// 每条曲线开口向上（a_i >= 0），凸函数的点态最大值仍是凸函数，
// 所以 F 在 [0,1000] 上单谷，直接三分求最小值。
double ternary_min() {
    double lo = 0.0;
    double hi = 1000.0;
    for (int iter = 0; iter < 100; iter++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (envelope(m1) < envelope(m2)) {
            hi = m2; // 谷底在左三分之二区间内
        } else {
            lo = m1; // 谷底在右三分之二区间内
        }
    }
    return envelope((lo + hi) / 2);
}

void solve() {
    ll t;
    cin >> t;
    for (ll k = 0; k < t; k++) {
        cin >> n;
        for (ll i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> c[i];
        }
        printf("%.4f\n", ternary_min());
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
