/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// brute.cpp：小数据暴力解，递归枚举所有分组方式，求最少组数。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int w, n;
int p[MAXN];        // 纪念品价格
int assigned[MAXN]; // assigned[i] = 1 表示第 i 个纪念品已分组
int ans;            // 最少组数

// 递归：每次找到第一个未分组的纪念品，决定它的分组方式
void dfs(int cur_groups) {
    // 找到第一个未分组的纪念品
    int first = -1;
    for (int i = 1; i <= n; i++) {
        if (!assigned[i]) {
            first = i;
            break;
        }
    }

    // 全部已分组，更新答案
    if (first == -1) {
        if (cur_groups < ans) ans = cur_groups;
        return;
    }

    // 剪枝：当前组数已经 >= 当前最优，不继续
    if (cur_groups >= ans) return;

    // 方案1：first 单独成组
    assigned[first] = 1;
    dfs(cur_groups + 1);
    assigned[first] = 0;

    // 方案2：first 和另一个未分组的纪念品配成一组（需满足 p ≤ w）
    for (int j = first + 1; j <= n; j++) {
        if (!assigned[j] && p[first] + p[j] <= w) {
            assigned[first] = 1;
            assigned[j] = 1;
            dfs(cur_groups + 1);
            assigned[first] = 0;
            assigned[j] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    ans = n;  // 最多 n 组（每个单独一组）
    dfs(0);

    cout << ans << '\n';
    return 0;
}
