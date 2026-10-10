/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 08:04
 * update_at: 2026-10-10 08:40
 */
#include <iostream>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;
const int MAXN = 200000 + 5;

ll fact[MAXN];     // fact[i] = i! mod MOD
ll inv_fact[MAXN]; // inv_fact[i] = (i!)^{-1} mod MOD

ll quick_power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        exp /= 2;
    }
    return res;
}

void init_comb(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[n] = quick_power(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

ll comb(int n, int m) {
    if (m < 0 || m > n) {
        return 0;
    }
    return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
}

// 第 pos 个数（从 1 开始）在最终答案中的系数。
ll coefficient(int n, int pos) {
    if ((n % 2 == 1) && (pos % 2 == 0)) {
        return 0;
    }
    int half_pos = (pos + 1) / 2;
    int half_n = (n + 1) / 2;
    ll c = comb(half_n - 1, half_pos - 1);
    if (half_pos % 2 == 0) {
        return -c;
    }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    init_comb(n);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll a = 0; // 预置 0：输入被截断时不读未初始化值
        cin >> a;
        ans = (ans + (a % MOD) * coefficient(n, i)) % MOD;
    }

    cout << (ans + MOD) % MOD << '\n';
    return 0;
}
