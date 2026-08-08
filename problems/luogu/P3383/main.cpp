#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000000;
const int MAXP = 6000005;

int n, q;
int k;
int prime_cnt;
int primes[MAXP];               // primes[i] 表示第 i 小素数（1 下标）
bitset<MAXN + 1> is_composite;  // 合数标记，bitset 节省内存

void linear_sieve(int limit) {
    for (int i = 2; i <= limit; i++) {
        if (!is_composite[i]) {
            primes[++prime_cnt] = i;
        }

        for (int j = 1; j <= prime_cnt; j++) {
            int p = primes[j];
            if (1LL * i * p > limit) {
                break;
            }
            is_composite[i * p] = 1;

            // p 已经是 i 的最小质因子时，后面的更大质数不能再拿来生成 i*p'。
            if (i % p == 0) {
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    linear_sieve(n);

    while (q--) {
        cin >> k;
        cout << primes[k] << '\n';
    }

    return 0;
}
