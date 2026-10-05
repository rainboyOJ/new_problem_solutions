/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:33
 * update_at: 2026-10-05 08:34
 */
#include <cstdio>

typedef long long ll;

const int MAXM = 15;
const int MAXN = 15;

ll memo[MAXM][MAXN]; // memo[m][n] = 把 m 点查克拉分给 n 个影分身（允许为 0）的方案数
bool vis[MAXM][MAXN]; // vis[m][n] 标记 memo[m][n] 是否已经求出

// f(m, n)：只看每个分身的点数构成的非递增序列，n=1 或 m=0 时方案唯一。
ll f(ll m, ll n) {
    if (m == 0 || n == 1) {
        return 1;
    }
    if (m < n) {
        return f(m, m); // 多出的分身只能拿 0 点，等价于没有它们
    }
    if (vis[m][n]) {
        return memo[m][n];
    }
    vis[m][n] = true;
    // 末位 a_n 为 0 -> f(m, n-1)；每个分身都至少 1 点 -> 全体减 1 -> f(m-n, n)
    memo[m][n] = f(m, n - 1) + f(m - n, n);
    return memo[m][n];
}

int main() {
    ll t;
    scanf("%lld", &t);
    for (ll i = 1; i <= t; i++) {
        ll m, n;
        scanf("%lld %lld", &m, &n);
        printf("%lld\n", f(m, n));
    }
    return 0;
}
