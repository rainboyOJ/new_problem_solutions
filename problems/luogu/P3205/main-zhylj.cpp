/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 10:19
 * update_at: 2026-10-24 10:19
 */
// main-zhylj.cpp：P3205 合唱队 的写法变体（f/g 双数组拉式）。
// 与 main.cpp 同一算法（区间 DP + 计数），区别只在写法：
//   1. 不用 dp[l][r][2] 三维表，改用 f/g 两个二维数组；
//   2. 转移写成「拉式」：长区间 [l,r] 从短区间 [l+1,r]、[l,r-1] 拉取；
//   3. 两个来源合并成一行，用 (h[x] < h[y]) 的真值当 0/1 系数。
// 写法灵感来自洛谷题解 zhylj (uid 34238) 的 f/g 双数组风格，代码为独立重写。
#include <bits/stdc++.h>
using namespace std;

const int MOD = 19650827;

static int h[1005]; // h[i]：理想队形中第 i 个人的身高（下标从 1 开始）
static int f[1005][1005]; // f[l][r]：已构成 [l,r]、最后插入的是左端 h[l] 的方案数
static int g[1005][1005]; // g[l][r]：已构成 [l,r]、最后插入的是右端 h[r] 的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    // 单点区间只记一边：单点的「最后插入者」左右端是同一个人，
    // 两边都置 1 会把方案数翻倍（n=1 的答案会变成 2）。
    for (int i = 1; i <= n; ++i) {
        f[i][i] = 1;
    }

    // 拉式转移：[l,r] 的最后插入者是 h[l] 时，上一步的区间是 [l+1,r]，
    // 要比的人是它的最后插入者（落在 h[l+1] 或 h[r] 上）；右端对称。
    // (h[x] < h[y]) 成立取 1、否则取 0，直接当系数，两个来源合并成一行。
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            f[l][r] = (f[l + 1][r] * (h[l] < h[l + 1]) + g[l + 1][r] * (h[l] < h[r])) % MOD;
            g[l][r] = (f[l][r - 1] * (h[l] < h[r]) + g[l][r - 1] * (h[r - 1] < h[r])) % MOD;
        }
    }

    cout << (f[1][n] + g[1][n]) % MOD << '\n';
    return 0;
}
