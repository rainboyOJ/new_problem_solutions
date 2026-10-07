/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:18
 * update_at: 2026-10-06 00:18
 */

#include <cstdio>

typedef long long ll;

const ll MOD = 10000; // 题目要求对 10^4 取模

// 2x2 矩阵乘法：c = a * b (mod MOD)，c 必须与 a、b 是不同的数组
void mat_mul(ll a[2][2], ll b[2][2], ll c[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
}

// 计算斐波那契数列第 n 项模 MOD，用转移矩阵的快速幂，复杂度 O(log n)
ll fib(ll n) {
    ll res[2][2] = {{1, 0}, {0, 1}};   // 单位矩阵，快速幂累积结果
    ll base[2][2] = {{1, 1}, {1, 0}};  // 斐波那契转移矩阵 A
    ll tmp[2][2];                       // 矩阵乘法的临时结果
    while (n > 0) {
        if (n & 1) {
            mat_mul(res, base, tmp);
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    res[i][j] = tmp[i][j];
                }
            }
        }
        mat_mul(base, base, tmp);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                base[i][j] = tmp[i][j];
            }
        }
        n >>= 1;
    }
    // A^n = [[F_{n+1}, F_n], [F_n, F_{n-1}]]，右上角元素恰好是 F_n
    return res[0][1];
}

int main() {
    ll n;
    while (scanf("%lld", &n) == 1) {
        if (n == -1) {
            break;
        }
        printf("%lld\n", fib(n));
    }
    return 0;
}
