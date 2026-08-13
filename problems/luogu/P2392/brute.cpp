/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:20
 * update_at: 2026-08-13 13:20
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举所有分法，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int s[4];        // s[i] 表示第 i 科的题目数量
int t[4][MAXN];  // t[i][j] 表示第 i 科第 j 道题的耗时
int n;           // 当前正在枚举的科的题目数量
int times[MAXN]; // 当前科的每道题耗时（从 t 拷贝过来）
int choose[MAXN]; // choose[i] = 0/1 表示第 i 题分给右脑 / 左脑
int best;        // 当前科的最优耗时

// 一条完整 01 序列已经生成，按选择统计两组时间并更新最优值。
void calc_answer() {
    int left_sum = 0, right_sum = 0;
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 1)
            left_sum += times[i];
        else
            right_sum += times[i];
    }
    int cost = max(left_sum, right_sum); // 这一科耗时 = 两边时间的较大值
    if (cost < best) best = cost;
}

// 枚举第 dep 道题的归属：0 给右脑，1 给左脑。
void dfs(int dep) {
    if (dep == n + 1) { // 一条完整的 01 序列已生成
        calc_answer();
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 4; i++) cin >> s[i];
    for (int i = 0; i < 4; i++)
        for (int j = 1; j <= s[i]; j++) cin >> t[i][j];

    int ans = 0;
    for (int i = 0; i < 4; i++) {
        n = s[i];
        for (int j = 1; j <= n; j++) times[j] = t[i][j];
        best = 0x7fffffff;
        dfs(1); // 枚举 2^n 种分法，只适合小数据
        ans += best;
    }
    cout << ans << '\n';
    return 0;
}
