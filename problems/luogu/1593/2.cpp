#include <iostream>
#include <vector>

using namespace std;

const int MOD = 9901;

// 快速幂计算 (base^exp) % MOD
long long qpow(long long base, long long exp) {
    long long res = 1;
    base %= MOD; // 这一点很重要，先取模防止溢出
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// 计算等比数列前 n+1 项和: 1 + p + ... + p^n
// 公式: (p^(n+1) - 1) / (p - 1)
long long sum_geometric(long long p, long long n) {
    // 情况 B: p % MOD == 1，此时 p-1 是 MOD 的倍数，逆元不存在
    // 序列变成 1 + 1 + ... + 1 (共 n+1 项)
    if ((p % MOD) == 1) { // 注意这里要判断 p % MOD
        return (n + 1) % MOD;
    }

    // 情况 A: p % MOD != 1，使用逆元求解
    // 分子: p^(n+1) - 1
    long long numerator = (qpow(p, n + 1) - 1 + MOD) % MOD; // +MOD防止减法出现负数
    
    // 分母: p - 1
    long long denominator = (p - 1) % MOD;
    
    // 逆元: (p-1)^(MOD-2)
    long long inv = qpow(denominator, MOD - 2);
    
    return (numerator * inv) % MOD;
}

int main() {
    int A, B;
    if (!(cin >> A >> B)) return 0;

    // 特殊情况处理
    if (A == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (B == 0) {
        cout << 1 << endl;
        return 0;
    }

    long long ans = 1;
    
    // 分解质因数
    // 遍历到 sqrt(A) 即可
    for (int i = 2; i * i <= A; ++i) {
        if (A % i == 0) {
            int count = 0;
            while (A % i == 0) {
                count++;
                A /= i;
            }
            // 此时找到了一个质因子 p = i，它的指数是 count
            // 在 A^B 中，质因子 p 的总指数是 count * B
            // 我们需要计算 1 + p + ... + p^(count*B)
            long long current_sum = sum_geometric(i, (long long)count * B);
            ans = (ans * current_sum) % MOD;
        }
    }

    // 如果 A > 1，说明剩下的 A 本身就是一个质数
    if (A > 1) {
        long long current_sum = sum_geometric(A, (long long)1 * B);
        ans = (ans * current_sum) % MOD;
    }

    cout << ans << endl;

    return 0;
}
