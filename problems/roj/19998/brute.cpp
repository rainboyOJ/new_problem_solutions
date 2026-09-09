/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:06
 * update_at: 2026-08-28 19:06
 */
// brute.cpp：小数据暴力解，使用选择序列递归枚举所有可能。
// 每一层递归在为"第 dep 个位置"选择候选值下标（1..k），
// 生成完整的 choose[] 后，在叶子节点按选出的序列跑标准 O(n^2) LIS，
// 所有方案里取最大的 LIS 长度就是答案。
// 只能处理很小的数据（k^n 种方案），用于对拍验证 main.cpp。
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 10;
const int MAXN = 15;

int k, n;
int cand[MAXN][MAXK]; // cand[i][j] = 第 i 个位置的第 j 个候选值
int choose[MAXN];     // choose[i] = 第 i 个位置选的候选值下标（1..k）
int seq[MAXN];        // 由 choose 生成的完整序列
int ans;

// 对当前完整选择序列 seq[1..n] 跑标准 O(n^2) 的 LIS，返回长度。
int calc_answer() {
    int dp[MAXN] = {0};
    int best = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int t = 1; t < i; t++) {
            if (seq[t] < seq[i]) dp[i] = max(dp[i], dp[t] + 1);
        }
        best = max(best, dp[i]);
    }
    return best;
}

// dfs(dep) 为第 dep 个位置选择候选值下标，生成完整选择序列后在叶子统计。
void dfs(int dep) {
    if (dep == n + 1) {
        for (int i = 1; i <= n; i++) seq[i] = cand[i][choose[i]];
        ans = max(ans, calc_answer());
        return;
    }

    // 这一层在选择第 dep 个位置用哪个候选值（共 k 种选择）。
    for (int c = 1; c <= k; c++) {
        choose[dep] = c;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> n;   // 注意输入顺序：k 在前，n 在后
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) cin >> cand[i][j];
    }

    dfs(1);
    cout << ans << '\n';
    return 0;
}