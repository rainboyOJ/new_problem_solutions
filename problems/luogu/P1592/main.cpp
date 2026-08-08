#include <bits/stdc++.h>
using namespace std;

long long n, k;

long long gcd_value(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// 用试除法计算单个 n 的欧拉函数 phi(n)。
long long euler_phi(long long x) {
    long long ans = x;

    for (long long p = 2; p * p <= x; p++) {
        if (x % p != 0) {
            continue;
        }

        ans = ans / p * (p - 1);
        while (x % p == 0) {
            x /= p;
        }
    }

    if (x > 1) {
        ans = ans / x * (x - 1);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    long long phi_n = euler_phi(n);

    // 每一段长度为 n 的区间里，与 n 互质的数的分布完全重复，
    // 并且每段恰好有 phi(n) 个。
    long long block_cnt = (k - 1) / phi_n;
    long long need = (k - 1) % phi_n + 1;

    long long cnt = 0;
    for (long long i = 1; i <= n; i++) {
        if (gcd_value(i, n) == 1) {
            cnt++;
            if (cnt == need) {
                cout << block_cnt * n + i << '\n';
                return 0;
            }
        }
    }

    return 0;
}
