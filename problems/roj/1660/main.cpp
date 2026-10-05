/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:38
 * update_at: 2026-10-06 01:38
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Big {
    static const ll BASE = 10000;
    vector<ll> d; // 低位在前，每元素 0~BASE-1

    Big(ll x = 0) {
        if (x == 0) d.push_back(0);
        else {
            while (x) {
                d.push_back(x % BASE);
                x /= BASE;
            }
        }
    }

    // 大整数乘以一个小整数（x <= 10000，结果仍精确）
    void mul(ll x) {
        ll carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            ll cur = d[i] * x + carry;
            d[i] = cur % BASE;
            carry = cur / BASE;
        }
        while (carry) {
            d.push_back(carry % BASE);
            carry /= BASE;
        }
        trim();
    }

    // 大整数减法：保证 *this >= b
    void sub(const Big& b) {
        ll borrow = 0;
        for (size_t i = 0; i < b.d.size(); ++i) {
            ll cur = d[i] - b.d[i] - borrow;
            if (cur < 0) {
                cur += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            d[i] = cur;
        }
        for (size_t i = b.d.size(); i < d.size() && borrow; ++i) {
            ll cur = d[i] - borrow;
            if (cur < 0) {
                cur += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            d[i] = cur;
        }
        trim();
    }

    void trim() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }

    void print() const {
        printf("%lld", d.back());
        for (int i = (int)d.size() - 2; i >= 0; --i) {
            printf("%04lld", d[i]);
        }
        printf("\n");
    }
};

const int MAXV = 10005;

int primes[MAXV];
int pcnt;
bool vis[MAXV];

// 线性筛，筛出 [2, n] 的所有质数
void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) primes[++pcnt] = i;
        for (int j = 1; j <= pcnt && i <= n / primes[j]; ++j) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

// n! 中质数 p 的指数
int count_p(int n, int p) {
    int cnt = 0;
    while (n) {
        n /= p;
        cnt += n;
    }
    return cnt;
}

// 计算 C(N, K)，通过质因数分解后累乘
Big comb(int N, int K) {
    Big res(1);
    for (int i = 1; i <= pcnt && primes[i] <= N; ++i) {
        int p = primes[i];
        int e = count_p(N, p) - count_p(K, p) - count_p(N - K, p);
        for (int j = 0; j < e; ++j) res.mul(p);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    sieve(n + m);
    Big ans = comb(n + m, m);
    Big bad = comb(n + m, m - 1);
    ans.sub(bad);
    ans.print();
    return 0;
}
