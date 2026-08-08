#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int MAXN = 1000000 + 5;

int n;
i64 mod;
int prime_cnt;
int primes[MAXN];
bool vis[MAXN];

// 线性筛出 1..limit 里的所有质数。
void get_primes(int limit) {
    for (int i = 2; i <= limit; i++) {
        if (!vis[i]) {
            primes[++prime_cnt] = i;
        }
        for (int j = 1; j <= prime_cnt; j++) {
            int p = primes[j];
            if (1LL * p * i > limit) {
                break;
            }
            vis[p * i] = true;
            if (i % p == 0) {
                break;
            }
        }
    }
}

// 计算质数 p 在 n! 中出现了多少次。
i64 count_in_factorial(int x, int p) {
    i64 ans = 0;
    while (x > 0) {
        x /= p;
        ans += x;
    }
    return ans;
}

i64 quick_pow(i64 base, i64 exp, i64 mod) {
    i64 ans = 1 % mod;
    base %= mod;

    while (exp > 0) {
        if (exp & 1LL) {
            ans = ans * base % mod;
        }
        base = base * base % mod;
        exp >>= 1LL;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> mod;

    if (mod == 1) {
        cout << 0 << '\n';
        return 0;
    }

    get_primes(2 * n);

    // Catalan(n) = C(2n, n) / (n + 1)
    // 用质因数分解来做，避免模数不一定是质数时不能直接求逆元。
    i64 ans = 1 % mod;
    for (int i = 1; i <= prime_cnt; i++) {
        int p = primes[i];
        i64 cnt = count_in_factorial(2 * n, p)
                - count_in_factorial(n, p)
                - count_in_factorial(n + 1, p);
        if (cnt > 0) {
            ans = ans * quick_pow(p, cnt, mod) % mod;
        }
    }

    cout << ans << '\n';

    return 0;
}
