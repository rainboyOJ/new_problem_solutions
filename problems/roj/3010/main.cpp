/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:44
 * update_at: 2026-10-06 13:44
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 9901; // 题面要求的取模常量

// 求等比和 1 + p + ... + p^(terms-1) 对 MOD 取模。
// 按 terms 的二进制从高位读到低位：每读一位先让项数翻倍，再决定是否补一项。
ll divsum(ll p, ll terms) {
    ll f = 0; // f = 1 + p + ... + p^(k-1)，k 是已经确定的项数
    ll g = 1; // g = p^k
    for (ll bit = 1LL << 40; bit > 0; bit >>= 1) {
        f = f * (g + 1) % MOD; // 项数翻倍：两段长度为 k 的等比串首尾相接
        g = g * g % MOD;
        if (terms & bit) {     // 当前位是 1：末尾再补一项 p^(2k)
            f = (f + g) % MOD;
            g = g * p % MOD;
        }
    }
    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    cin >> a >> b;

    if (a == 0) { // 本题数据约定：0 的约数和取 0
        cout << 0 << "\n";
        return 0;
    }

    // 分解 A = ∏ p^e，对每个质因子的等比和相乘
    ll ans = 1;
    ll n = a;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p != 0) continue;
        ll e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        ans = ans * divsum(p % MOD, e * b + 1) % MOD; // 该括号共有 e*B+1 项
    }
    if (n > 1) { // 除完小因子后剩下的部分本身就是质数，指数为 1
        ans = ans * divsum(n % MOD, b + 1) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
