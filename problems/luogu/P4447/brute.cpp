/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-20 13:47
 * update_at: 2026-10-22 23:20
 */
// brute.cpp：小数据暴力解，使用「分组编号序列」递归枚举所有分法。
//
// 这一层枚举的是「第 dep 个队员分到第几个组」，每个位置有 n 种选择（组号 1..n），
// 共 n^n 种。到叶子节点时统一检查合法性：
//   1. 每组内数值互不相同；
//   2. 每组内数值排序后相邻恰好差 1（即连续）。
// 全部合法就用「人数最少的组的人数」去更新答案。
//
// 组号本身没有标号意义，所以同一个划分会被重复枚举（比如两人一组时组号可交换），
// 但这只影响枚举次数，不影响 max-min 的结果，暴力不必去重。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n;
int a[MAXN];

int belong[MAXN];  // belong[i] = 第 i 个队员被分到的组号（1..n）

int best_answer;  // 所有合法方案中「最小组人数」的最大值

// 到叶子节点：belong[] 已给出完整分法，检查它是否合法并更新答案
void check() {
    // 按组号收集每组的成员
    vector<int> group[MAXN];
    for (int i = 1; i <= n; i++) {
        group[belong[i]].push_back(a[i]);
    }

    int min_size = n;  // 本方案里人数最少的组的人数
    for (int g = 1; g <= n; g++) {
        if (group[g].empty()) continue;

        sort(group[g].begin(), group[g].end());

        // 条件一：组内不能有两个相同的实力值
        for (int k = 1; k < (int)group[g].size(); k++) {
            if (group[g][k] == group[g][k - 1]) return;
        }
        // 条件二：相邻两项必须恰好差 1（排序后连续）
        for (int k = 1; k < (int)group[g].size(); k++) {
            if (group[g][k] != group[g][k - 1] + 1) return;
        }

        min_size = min(min_size, (int)group[g].size());
    }

    best_answer = max(best_answer, min_size);
}

// 这一层在决定「第 dep 个队员分到第几组」
void dfs(int dep) {
    if (dep > n) {
        check();
        return;
    }
    for (int g = 1; g <= n; g++) {
        belong[dep] = g;
        dfs(dep + 1);
    }
    belong[dep] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    best_answer = 0;
    dfs(1);
    cout << best_answer << '\n';
    return 0;
}
