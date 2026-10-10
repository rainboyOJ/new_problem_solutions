/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:20
 * update_at: 2026-10-08 04:20
 */
// 一本通 1805《数数》：统计等差数列 B+A, B+2A, ..., B+N*A 共 N 项
// 的二进制表示中 1 的总个数，T 组询问。
//
// 核心：按二进制位拆分贡献。第 k 位是否为 1 可用
//   bit_k(x) = floor(x / 2^k) - 2 * floor(x / 2^{k+1})
// 精确表示，于是答案 = Σ_k ( S_k - 2 * S_{k+1} )，
// 其中 S_k = Σ_{i=1}^{N} floor((B + i*A) / 2^k) = f(A, A+B, 2^k, N-1)。
// f 用类欧几里得（辗转相除式）递归在 O(log) 内求出。
#include <cstdio>

typedef long long ll;
typedef __int128 i128;

// f(a, b, c, n) = Σ_{i=0}^{n} floor((a*i + b) / c)，要求 a,b,c >= 0，n >= 0。
// 每层递归都对 c 取模，规模呈对数级衰减，递归深度 O(log c)。
i128 floor_sum(i128 a, i128 b, i128 c, i128 n) {
    if (a == 0) return (b / c) * (n + 1);                        // 水平线，直接算
    if (a >= c || b >= c) {                                      // 拆出整除部分
        return floor_sum(a % c, b % c, c, n)
             + n * (n + 1) / 2 * (a / c)
             + (n + 1) * (b / c);
    }
    i128 max_y = (a * n + b) / c;                                // 斜率 < 1，转置坐标轴
    if (max_y == 0) return 0;                                    // 一格都数不到
    return n * max_y - floor_sum(c, c - b - 1, a, max_y - 1);
}

// 输出 __int128（答案最大约 5.5e13，但中间量到 1e28，故统一用 128 位）
void print_i128(i128 x) {
    if (x == 0) { putchar('0'); return; }
    char buf[64];
    int len = 0;
    // 这里必须把 __int128 窄化成 int 才能做字符运算，属于对内存类型的必要转换
    while (x > 0) { buf[len++] = '0' + int(x % 10); x /= 10; }
    while (len > 0) putchar(buf[--len]);
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        ll A, B, N;
        scanf("%lld %lld %lld", &A, &B, &N);
        ll limit = B + A * N;            // 数列最大项，<= 2e16 < 2^55，ll 不会溢出
        i128 ans = 0;
        for (ll power = 1; power <= limit; power *= 2) {
            // S_k = Σ_{i=1}^{N} floor((B + i*A) / 2^k)
            i128 sum_low = floor_sum(A, A + B, power, N - 1);
            i128 sum_high = floor_sum(A, A + B, power * 2, N - 1);
            ans += sum_low - 2 * sum_high;   // 第 k 位上 1 的出现次数
        }
        print_i128(ans);
        putchar('\n');
    }
    return 0;
}
