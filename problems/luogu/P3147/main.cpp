/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 12:46
 * update_at: 2026-10-26 12:46
 */
// main.cpp：反转状态维度的 DP。朴素区间 DP 的状态是 (左端点, 右端点)，共 O(n^2)；
// 本题的值域很小(答案不超过 58)，于是把"值"当状态维度，用"位置"当存下来的结果：
// dp[i][v] = 从位置 i 开始能整段合成值 v 时最短的结束位置(0 表示合成不出来)。
// 转移：先把 [i, mid] 合成一个 v-1，再接着把 [mid+1, …] 合成一个 v-1，两个 v-1
// 相邻就能合成 v。按 v 从小到大递推即可。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 262144 + 5; // n <= 262144
// 答案上界：初始值 <= 40，每次合并只让值涨 1，而长度为 n 的区间最多合并 n-1 次。
// n <= 2^18，所以最大值为 40 + 18 = 58，取 60 留出余量。
const int MAXV = 62;

int n;
int a[MAXN]; // a[i]：序列第 i 个数（1-based）

// dp[i][v]：从位置 i 开始，最短到哪个位置结束可以把这段区间合成一个值 v。
// 用 1-based 的结束位置，0 表示合成不出来。
int dp[MAXN][MAXV];

int main() {
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        dp[i][a[i]] = i; // 单个元素本身就是 a[i]，结束位置就是它自己
        if (a[i] > ans) {
            ans = a[i]; // 一个数都不合并时，答案至少是初始最大值
        }
    }

    // 按值从小到大递推：dp[i][v] 只依赖 v-1 那一层。
    for (int v = 2; v < MAXV; v++) {
        for (int i = 1; i <= n; i++) {
            int mid = dp[i][v - 1];
            if (mid == 0) {
                continue; // 左边这一段都合不出 v-1
            }
            if (mid + 1 > n || dp[mid + 1][v - 1] == 0) {
                continue; // 右边凑不出第二个相邻的 v-1
            }
            dp[i][v] = dp[mid + 1][v - 1];
            if (v > ans) {
                ans = v;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
