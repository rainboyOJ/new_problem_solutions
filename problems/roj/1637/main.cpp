/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:57
 * update_at: 2026-10-05 23:57
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 20;

ll n;
ll C[MAXN], P[MAXN], L[MAXN]; // 第 i 个野人的初始山洞编号、每年前进洞数、寿命

// 扩展欧几里得：求 a*x + b*y = gcd(a,b)，返回最大公约数 g
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, x, y);
    ll tmp = y;
    y = x - (a / b) * y;
    x = tmp;
    return g;
}

// 判断野人 i 与野人 j 在 mod m 下是否会在共同寿命内相遇
// 相遇条件：(P_i - P_j) * x ≡ C_j - C_i (mod m)，x 为年数
bool can_meet(int i, int j, ll m) {
    ll a = P[i] - P[j];
    ll b = C[j] - C[i];
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if (b % g != 0) {
        return false; // 无整数解，两人永不相遇
    }
    ll step = m / g;
    if (step < 0) {
        step = -step;
    }
    x = x * (b / g) % step; // 最小非负整数解
    if (x < 0) {
        x += step;
    }
    ll limit = min(L[i], L[j]);
    return x <= limit; // 解落在共同寿命内即冲突
}

// 检验山洞总数为 m 时，是否所有野人两两都不相遇
bool is_valid_m(ll m) {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (can_meet(i, j, m)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ll start = 0; // 山洞数至少要不小于所有初始位置的最大值
    for (int i = 1; i <= n; i++) {
        cin >> C[i] >> P[i] >> L[i];
        if (C[i] > start) {
            start = C[i];
        }
    }

    // 保证有解且 M <= 10^6，从下界开始递增枚举
    for (ll m = start; ; m++) {
        if (is_valid_m(m)) {
            cout << m << "\n";
            break;
        }
    }

    return 0;
}
