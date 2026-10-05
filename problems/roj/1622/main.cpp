/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:18
 * update_at: 2026-10-06 01:18
 */
// roj 1622 Goldbach's Conjecture：欧拉筛预处理素数表，逐组贪心取最小奇素数 a。
#include <iostream>
#include <vector>

typedef long long ll;

const int MAXN = 1000000; // 题面保证 6 <= n <= 10^6

bool is_prime[MAXN + 1]; // is_prime[x] 表示 x 是否为素数
std::vector<int> primes;  // 按升序保存 [2, MAXN] 内的所有素数

// 欧拉筛：O(MAXN) 预处理素数表与素数判定表。
void build_sieve() {
    for (int i = 0; i <= MAXN; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < (int)primes.size(); j++) {
            ll product = (ll)i * primes[j];
            if (product > MAXN) {
                break;
            }
            is_prime[product] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    build_sieve();
    ll n;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }
        // b - a = n - 2a 随 a 增大而减小，故取最小的奇素数 a 即为最优解。
        bool found = false;
        for (int i = 0; i < (int)primes.size(); i++) {
            ll a = primes[i];
            if (a > n / 2) {
                break;
            }
            if (a == 2) {
                continue; // 只取奇素数，2 留给其他分解
            }
            ll b = n - a;
            if (is_prime[b]) {
                std::cout << n << " = " << a << " + " << b << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Goldbach's conjecture is wrong.\n";
        }
    }
    return 0;
}
