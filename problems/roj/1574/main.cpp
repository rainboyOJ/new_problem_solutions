/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:42
 * update_at: 2026-10-05 09:42
 */
// roj/1574 矩阵取数游戏：行间独立，逐行做两端取数的区间 DP。
// 答案上界约 80*1000*2^81 < 2^98，超过 64 位但远小于 2^128，用 __int128 承接。
#include <cstdio>

typedef long long ll;

const int MAXM = 85; // m <= 80，dp 表按单行最大长度开

ll a[MAXM];               // 当前行的元素，a[1..m] 对应题面从左到右
__int128 dp[MAXM][MAXM];  // dp[l][r]：把当前行剩余段 a[l..r] 取完能得到的最高得分
ll n, m;

// 输出 __int128：答案约 1.9e29，用扩展整数承接，省去手写高精度。
void print_int128(__int128 x) {
    if (x == 0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[64];
    int len = 0;
    while (x > 0) {
        int digit = x % 10;
        buf[len] = '0' + digit;
        len++;
        x /= 10;
    }
    while (len > 0) {
        len--;
        putchar(buf[len]);
    }
    putchar('\n');
}

// 单行最优得分：剩余段长度从 1 递推到 m，长段只依赖短段。
__int128 row_best() {
    for (int i = 1; i <= m; i++) {
        // 只剩一个元素时两侧已取走 m-1 个，它必是第 m 轮，权重 2^m
        __int128 weight = 1;
        weight = weight << m;
        dp[i][i] = weight * a[i];
    }
    for (int len = 2; len <= m; len++) {
        for (int l = 1; l + len - 1 <= m; l++) {
            int r = l + len - 1;
            int pick = m - (r - l); // 本次是第 pick 轮，轮次只由剩余段长度决定
            __int128 weight = 1;
            weight = weight << pick;
            // 本次只能取行首或行尾，两种取法各自加上剩余段的最优得分
            __int128 take_left = dp[l + 1][r] + weight * a[l];
            __int128 take_right = dp[l][r - 1] + weight * a[r];
            if (take_left > take_right) {
                dp[l][r] = take_left;
            } else {
                dp[l][r] = take_right;
            }
        }
    }
    return dp[1][m];
}

void solve() {
    scanf("%lld %lld", &n, &m);
    __int128 answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[j]);
        }
        // 每轮每行各取一个、权重只与轮次有关，各行互不影响，总分即各行最优之和
        answer = answer + row_best();
    }
    print_int128(answer);
}

int main() {
    solve();
    return 0;
}
