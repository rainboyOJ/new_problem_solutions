/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:34
 * update_at: 2026-10-06 18:34
 */
#include <iostream>
using namespace std;

const int MOD = 10007;
const int MAXK = 1005;

typedef long long ll;

ll a, b, k, n, m;

// 组合数 C(k,n) mod MOD，用递推公式 C(i,j)=C(i-1,j-1)+C(i-1,j)
ll C[MAXK][MAXK]; // C[i][j] 表示从 i 个里选 j 个的方案数

// 快速幂：计算 base^exp mod MOD
ll qpow(ll base, ll exp) {
    ll res = 1 % MOD;
    base = base % MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

void solve() {
    // 递推求组合数，k <= 1000，数组直接开
    for (ll i = 0; i <= k; i++) {
        C[i][0] = 1; // 从 i 个里选 0 个，方案数为 1
        for (ll j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    ll comb = C[k][n]; // 从 k 个括号里选 n 个挑 ax 的方案数
    ll pa = qpow(a, n); // a^n mod MOD
    ll pb = qpow(b, m); // b^m mod MOD

    ll ans = comb * pa % MOD * pb % MOD;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> k >> n >> m;
    solve();

    return 0;
}
