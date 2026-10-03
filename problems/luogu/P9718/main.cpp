/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 12:31
 * update_at: 2026-10-03 12:31
 */
// P9718 [EC Final 2022] Best Carry Player 2
// 求最小的正整数 y，使 x + y 的竖式加法中「进位次数」恰好为 k，无解输出 -1。
//
// 核心模型：把 x 从低位到高位写成 a[0..n-1]，y 的同位数字记作 b[i]。
// 设 c[i] 表示第 i 位向第 i+1 位的进位（c[0]=0），则
//   c[i+1] = 1 等价于 a[i] + b[i] + c[i] >= 10。
// 于是「进位次数」= 进位集合 { i : c[i+1]=1 } 的大小。
//
// 一个位置要想「新产生」进位，必须 a[i] + c[i] + b[i] >= 10，即
//   - c[i]=0 时需要 a[i] >= 1，最小 b[i] = 10 - a[i]（把和顶到 10）；
//   - c[i]=1 时需要 b[i] >= 9 - a[i]，最小 b[i] = 9 - a[i]。
// 注意 c[i]=0 且 a[i]=0 时即使 b[i]=9 也只能得到 9，无法产生进位，
// 所以每个进位段的首位必须满足 a[i] >= 1。
// 同理，「进位到此为止」需要 a[i] + b[i] + c[i] <= 9：
//   - c[i]=1 时最小代价 b[i]=0，且要求 a[i] <= 8（a[i]=9 时无法停下）。
//
// 于是问题变成：在数位上选出恰好 k 个进位位置，使 y 的值最小。
// 用 dp[c][j] = 处理完前 i 位后、当前进位状态为 c、已产生 j 次进位时 y 的最小值，
// 从低位向高位转移即可；每一位的代价 b[i] 会乘以 10^i。
// 超出 x 长度的位置 a[i]=0，此时：
//   - c=0 什么也不做，代价 0；
//   - c=1 一路继续 j' 位，最小 y 是 1 后跟 (n + j') 个 0（即 10^(n+j')）。
// 答案可能达到 10^36 量级，用 unsigned __int128 存下绰绰有余。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 20;      // x < 10^18，位数不超过 18
const int MAXK = 20;      // k <= 18
const int MAXP = 45;      // 10^36 < 2^128，够用

unsigned __int128 pow10u[MAXP];              // pow10u[i] = 10^i
unsigned __int128 dp[2][MAXK];               // dp[进位状态][已用进位次数]
unsigned __int128 ndp[2][MAXK];
int a[MAXN + 1];                             // x 从低到高的各位数字
int n;                                       // x 的位数

const unsigned __int128 U128_INF = ~(unsigned __int128)0;

// unsigned __int128 没有现成的输出，手动转十进制
void print_u128(unsigned __int128 v) {
    char s[64];
    int len = 0;
    if (v == 0) {
        putchar('0');
        return;
    }
    while (v > 0) {
        s[len++] = char('0' + (int)(v % 10));
        v /= 10;
    }
    while (len > 0) {
        putchar(s[--len]);
    }
}

// 拆出 x 的每一位，a[0] 是最低位
void split_digits(unsigned long long x) {
    n = 0;
    while (x > 0) {
        a[n++] = (int)(x % 10);
        x /= 10;
    }
    if (n == 0) {
        a[n++] = 0;
    }
}

void solve_one(unsigned long long x, int k) {
    split_digits(x);

    // k = 0 的情况：y 的每一位都不能和 x 产生进位
    // 只要某一位 a[i] <= 8，该位取 b[i] = 10 - a[i]（a[i]=0 时取 0）即可，
    // 更低的位全部取 0，所以答案是 10^i（i 是最小的满足 a[i] <= 8 的下标）。
    // 若 x 全是 9，则取 y = 10^n，此时 a[i]=0（i=n）满足条件。
    if (k == 0) {
        int i = 0;
        while (i < n && a[i] == 9) {
            i++;
        }
        print_u128(pow10u[i]);
        putchar('\n');
        return;
    }

    // 初始：还没处理任何位，进位状态 0，已用 0 次进位，y 的值 0
    for (int c = 0; c < 2; c++) {
        for (int j = 0; j <= k; j++) {
            dp[c][j] = U128_INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 2; c++) {
            for (int j = 0; j <= k; j++) {
                ndp[c][j] = U128_INF;
            }
        }
        unsigned __int128 w = pow10u[i];   // 第 i 位的权值
        for (int c = 0; c < 2; c++) {
            for (int j = 0; j <= k; j++) {
                if (dp[c][j] == U128_INF) {
                    continue;
                }
                if (c == 0) {
                    // 不产生进位：b[i] = 0
                    if (dp[c][j] < ndp[0][j]) {
                        ndp[0][j] = dp[c][j];
                    }
                    // 新产生一次进位：要求 a[i] >= 1，b[i] = 10 - a[i]
                    if (a[i] >= 1 && j + 1 <= k) {
                        unsigned __int128 val = dp[c][j] + (unsigned __int128)(10 - a[i]) * w;
                        if (val < ndp[1][j + 1]) {
                            ndp[1][j + 1] = val;
                        }
                    }
                } else {
                    // 进位结束：要求 a[i] <= 8，b[i] = 0
                    if (a[i] <= 8 && dp[c][j] < ndp[0][j]) {
                        ndp[0][j] = dp[c][j];
                    }
                    // 进位继续：b[i] = 9 - a[i]，又产生一次进位
                    if (j + 1 <= k) {
                        unsigned __int128 val = dp[c][j] + (unsigned __int128)(9 - a[i]) * w;
                        if (val < ndp[1][j + 1]) {
                            ndp[1][j + 1] = val;
                        }
                    }
                }
            }
        }
        for (int c = 0; c < 2; c++) {
            for (int j = 0; j <= k; j++) {
                dp[c][j] = ndp[c][j];
            }
        }
    }

    unsigned __int128 ans = U128_INF;

    // 结尾一：不进位，必须恰好用满 k 次进位
    if (dp[0][k] < ans) {
        ans = dp[0][k];
    }

    // 结尾二：第 n-1 位产生了进位，即 c[n]=1。此时最高位之外 a[i]=0，
    // 补 b[i]=9 可以让进位继续：0 + 9 + 1 = 10，又记账一次进位。
    // 设还需要 rem = k - j 次进位，就要在第 n ~ n+rem-1 位都补 9，
    // 代价为 9 * (10^n + ... + 10^(n+rem-1)) = 10^(n+rem) - 10^n。
    // rem = 0 时代价为 0：该位取 b=0 即可让最终悬挂的进位停下。
    for (int j = 0; j <= k; j++) {
        if (dp[1][j] == U128_INF) {
            continue;
        }
        int rem = k - j;
        unsigned __int128 val = dp[1][j] + pow10u[n + rem] - pow10u[n];
        if (val < ans) {
            ans = val;
        }
    }

    if (ans == U128_INF) {
        puts("-1");
    } else {
        print_u128(ans);
        putchar('\n');
    }
}

int main() {
    pow10u[0] = 1;
    for (int i = 1; i < MAXP; i++) {
        pow10u[i] = pow10u[i - 1] * 10;
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        unsigned long long x;
        int k;
        scanf("%llu %d", &x, &k);
        solve_one(x, k);
    }
    return 0;
}
