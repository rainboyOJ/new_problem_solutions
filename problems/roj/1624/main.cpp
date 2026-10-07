/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:10
 * update_at: 2026-10-05 23:12
 */
// main.cpp：正解。把 1/x + 1/y = 1/n! 变形为 (x-n!)(y-n!)=(n!)^2，
// 正整数解数目 = (n!)^2 的约数个数，用线性筛分解 1..n 求质因子指数后连乘。
#include <iostream>

typedef long long ll;

const int MAXN = 1000000 + 5; // n 的上界
const ll MOD = 1000000007;

int min_prime[MAXN]; // min_prime[v] = v 的最小质因子，线性筛中顺带求出
int primes[MAXN]; // primes[1..prime_cnt] 存放筛出的质数
int prime_cnt;
ll exp_of_prime[MAXN]; // exp_of_prime[p] = p 在 n! 中的指数

int n;

// 线性筛：每个合数只被它的最小质因子筛掉一次，同时记录最小质因子。
void linear_sieve() {
    for (int v = 2; v <= n; v++) {
        if (min_prime[v] == 0) { // 没有更小的质因子，说明 v 是质数
            min_prime[v] = v;
            prime_cnt++;
            primes[prime_cnt] = v;
        }
        for (int i = 1; i <= prime_cnt; i++) {
            int p = primes[i];
            if (p > min_prime[v] || p > n / v) { // p * v > n 时停止
                break;
            }
            min_prime[p * v] = p;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;

    linear_sieve();

    // 把 2..n 每个数分解质因数，指数累加得到 n! 的标准分解。
    for (int i = 2; i <= n; i++) {
        int x = i; // 用临时变量分解，不能改动外层循环变量 i
        while (x > 1) {
            int p = min_prime[x];
            while (x % p == 0) {
                x /= p;
                exp_of_prime[p]++;
            }
        }
    }

    // 答案 = d((n!)^2) = ∏ (2 * e_p + 1)，其中 e_p 是 p 在 n! 中的指数。
    ll answer = 1;
    for (int i = 1; i <= prime_cnt; i++) {
        int p = primes[i];
        answer = answer * (2 * exp_of_prime[p] + 1) % MOD;
    }

    std::cout << answer << "\n";
    return 0;
}
