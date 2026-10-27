/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:59
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 35;
const int MAXV = 105;
int n, V;
int v[MAXN], w[MAXN];
int f[MAXN][MAXV]; // f[i][c] 表示考虑前 i 件物品，容量为 c 时的最大价值

vector<int> path;          // 当前 DFS 枚举的路径（逆序）
vector<vector<int>> all;   // 所有最优方案

// 从物品 i 向 1 回溯，找出所有能达到 f[i][c] 的方案
void dfs(int i, int c) {
    if (i == 0) {
        // 到边界，记录一条完整方案（path 中编号从大到小，需要反转）
        vector<int> sol = path;
        reverse(sol.begin(), sol.end());
        all.push_back(sol);
        return;
    }

    // 分支1：不选物品 i，要求 f[i-1][c] 也能达到相同最优值
    if (f[i - 1][c] == f[i][c]) {
        dfs(i - 1, c);
    }

    // 分支2：选物品 i，要求容量足够且来自该转移
    if (c >= v[i] && f[i - 1][c - v[i]] + w[i] == f[i][c]) {
        path.push_back(i);
        dfs(i - 1, c - v[i]);
        path.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> V;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    // 正序 01 背包 DP
    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c <= V; ++c) {
            f[i][c] = f[i - 1][c];
            if (c >= v[i]) f[i][c] = max(f[i][c], f[i - 1][c - v[i]] + w[i]);
        }
    }

    // 找出最大价值及其对应的容量
    int best_val = 0;
    for (int c = 0; c <= V; ++c) best_val = max(best_val, f[n][c]);

    // 对所有能达到 best_val 的容量 c，回溯收集方案
    for (int c = 0; c <= V; ++c) {
        if (f[n][c] == best_val) {
            dfs(n, c);
        }
    }

    // 按字典序排序后输出
    sort(all.begin(), all.end());
    for (size_t i = 0; i < all.size(); ++i) {
        const vector<int> &sol = all[i];
        for (size_t j = 0; j < sol.size(); ++j) {
            if (j > 0) cout << ' ';
            cout << sol[j];
        }
        cout << '\n';
    }
    return 0;
}
