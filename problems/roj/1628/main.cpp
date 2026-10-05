/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:14
 * update_at: 2026-10-05 23:14
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXP = 1024; // x <= 2^20，试除到 sqrt(x) <= 1024 即可

int primes[200]; // 预处理得到的 <= 1024 的素数
int prime_cnt;   // 素数个数

ll fact[64]; // fact[i] = i!，x <= 2^20 时质因子总个数 k <= 20

// 埃氏筛预处理 <= MAXP 的素数，供试除分解质因数使用。
void init_primes() {
    bool is_prime[MAXP + 1];
    for (int i = 0; i <= MAXP; i++) is_prime[i] = true;
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i * i <= MAXP; i++) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= MAXP; j += i) is_prime[j] = false;
    }
    prime_cnt = 0;
    for (int i = 2; i <= MAXP; i++) {
        if (is_prime[i]) primes[prime_cnt++] = i;
    }
}

// 预处理阶乘，用于计算多重集排列数。
void init_fact() {
    fact[0] = 1;
    for (int i = 1; i < 64; i++) fact[i] = fact[i - 1] * i;
}

// 对单个 x 求答案：最大链长 = 质因子指数之和 k，方案数 = k! / (各指数阶乘之积)。
void solve_one(ll x) {
    ll total = 0; // 质因子指数之和，即最大链长 k
    ll denom = 1; // 分母：各质因子指数阶乘的乘积
    ll rest = x;
    for (int i = 0; i < prime_cnt; i++) {
        ll p = primes[i];
        if (p * p > rest) break;
        if (rest % p == 0) {
            ll cnt = 0;
            while (rest % p == 0) {
                rest /= p;
                cnt++;
            }
            total += cnt;
            denom *= fact[cnt];
        }
    }
    if (rest > 1) total += 1; // 剩下一个大于 1 的质因子
    cout << total << " " << fact[total] / denom << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_primes();
    init_fact();

    ll x;
    while (cin >> x) { // 多组数据读到文件结束
        solve_one(x);
    }

    return 0;
}
