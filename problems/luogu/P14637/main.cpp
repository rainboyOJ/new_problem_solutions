/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 09:55
 * update_at: 2026-11-01 09:55
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8005;
// n<=8000；答案和所有中间 DP 值均不超过 (m+2)n，int 足够。
int n, m, level;
vector<int> child[MAXN];
int subtree_size[MAXN], height[MAXN], heavy[MAXN];

// 固定 level 后，分别是 F(u,level)、G(u,level)、G(u,level+1)。
int free_dp[MAXN], chain_dp[MAXN], next_chain[MAXN];
int side_sum[MAXN], offset[MAXN];
int pool[MAXN], used;
int *best[MAXN]; // best[u][d]+offset[u] 是距离 u 为 d-1 的最优候选。

void prepare_tree(int u) {
    subtree_size[u] = height[u] = 1;
    heavy[u] = 0;
    for (int v : child[u]) {
        prepare_tree(v);
        subtree_size[u] += subtree_size[v];
        if (height[v] + 1 > height[u]) {
            height[u] = height[v] + 1;
            heavy[u] = v;
        }
    }
}

void dfs_dp(int u) {
    if (best[u] == nullptr) {
        best[u] = pool + used;
        used += height[u];
    }
    if (heavy[u]) best[heavy[u]] = best[u] + 1;

    int sum = 0;
    for (int v : child[u]) {
        dfs_dp(v);
        sum += free_dp[v];
    }

    free_dp[u] = chain_dp[u] = level * subtree_size[u];
    for (int v : child[u]) {
        side_sum[v] = sum - free_dp[v];
        chain_dp[u] = max(chain_dp[u], level + next_chain[v] + side_sum[v]);
    }

    // 接重儿子的数组只平移指针；整段增加的旁支贡献交给 offset。
    if (heavy[u]) {
        int v = heavy[u];
        offset[u] = offset[v] + side_sum[v];
        for (int w : child[u]) {
            if (w == v) continue;
            for (int d = 1; d <= height[w]; d++) {
                int candidate = best[w][d] + offset[w] + side_sum[w] - offset[u];
                best[u][d + 1] = max(best[u][d + 1], candidate);
            }
        }
    }
    best[u][1] = chain_dp[u] - offset[u];
    if (height[u] >= level) {
        int candidate = best[u][level] + offset[u] + level * (level - 1);
        free_dp[u] = max(free_dp[u], candidate);
    }
}

void solve() {
    cin >> n >> m;
    for (int u = 1; u <= n; u++) child[u].clear();
    for (int u = 2; u <= n; u++) {
        int parent;
        cin >> parent;
        child[parent].push_back(u);
    }
    prepare_tree(1);

    for (int u = 1; u <= n; u++) chain_dp[u] = (m + 2) * subtree_size[u];
    for (level = m + 1; level >= 1; level--) {
        used = 0;
        fill(pool, pool + n + 1, 0);
        for (int u = 1; u <= n; u++) {
            best[u] = nullptr;
            offset[u] = 0;
            next_chain[u] = chain_dp[u];
        }
        dfs_dp(1);
    }
    cout << chain_dp[1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) solve();
    return 0;
}
