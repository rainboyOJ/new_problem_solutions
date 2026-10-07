/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:12
 * update_at: 2026-10-06 00:12
 */

// main.cpp：Fibonacci 第 n 项 —— 2x2 矩阵快速幂。
// 递推矩阵 M = [[1,1],[1,0]]，f_n 就是 M^(n-1) 的左上角；
// n 可到 2e9，必须用快速幂把 O(n) 递推降到 O(log n)。

#include <cstdio>

typedef long long ll;

ll m; // 模数

// 2x2 矩阵，固定大小直接用全局函数处理
struct Mat {
    ll a[2][2];
};

// 矩阵乘法，结果每个元素都取模
Mat mul(const Mat &x, const Mat &y) {
    Mat z;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            ll sum = 0;
            for (int k = 0; k < 2; ++k)
                sum += x.a[i][k] * y.a[k][j]; // 每项 < m^2 < 2e18，不溢出
            z.a[i][j] = sum % m;
        }
    return z;
}

// 计算 M^e 的左上角：指数二进制拆分，base 每轮平方，该位为 1 时先乘入再平方
ll fib_pow(ll e) {
    Mat base; // base 表示 M^(2^b)，b 是当前扫到的二进制位
    base.a[0][0] = 1; base.a[0][1] = 1;
    base.a[1][0] = 1; base.a[1][1] = 0;

    Mat result; // result 累乘已经扫过的 M^(2^b_i)，初始为单位矩阵 M^0
    result.a[0][0] = 1; result.a[0][1] = 0;
    result.a[1][0] = 0; result.a[1][1] = 1;

    while (e > 0) {
        if (e & 1) result = mul(result, base);
        base = mul(base, base);
        e >>= 1;
    }
    return result.a[0][0]; // M^e 的左上角就是 f_(e+1)
}

int main() {
    ll n; // 要求的项数
    scanf("%lld %lld", &n, &m);

    // 指数为 0（n=1）时 result 是单位矩阵，左上角 1 = f_1，无需特判
    printf("%lld\n", fib_pow(n - 1));
    return 0;
}
