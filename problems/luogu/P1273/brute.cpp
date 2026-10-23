/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:32
 * update_at: 2026-10-23 23:33
 */
/*
 * 暴力解法说明：
 * 枚举所有用户终端（共有 M 个）的子集，共 2^M 种状态。
 * 对于每个被选中的用户子集：
 * 1. 信号必须从根节点 1 传输到所有被选中的用户，因此需要覆盖连接这些用户到根节点的连通子树。
 * 2. 统计树上被激活的边的权值总和（成本），并计算被选中用户的付费总和（收入）。
 * 3. 若 收入 - 成本 >= 0，则更新最大合法用户数。
 * 时间复杂度为 O(2^M * N)，只适合 M <= 20 的小规模测试数据。
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 105;

struct Edge {
    int to;
    ll w;
};

ll n, m;
vector<Edge> g[MAXN];
ll val[MAXN];
int parent_node[MAXN];
ll parent_edge_cost[MAXN];

void get_parents(int u, int p) {
    for (const auto &e : g[u]) {
        int v = e.to;
        if (v == p) continue;
        parent_node[v] = u;
        parent_edge_cost[v] = e.w;
        get_parents(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n - m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int to;
            ll cost;
            cin >> to >> cost;
            g[i].push_back({to, cost});
        }
    }

    for (int i = n - m + 1; i <= n; ++i) {
        cin >> val[i];
    }

    get_parents(1, 0);

    ll ans = 0;
    // 枚举 2^m 种叶子选择方案
    int total_masks = 1 << m;
    for (int mask = 0; mask < total_masks; ++mask) {
        ll cnt = 0;
        ll income = 0;
        vector<bool> edge_used(n + 1, false);

        for (int i = 0; i < m; ++i) {
            if ((mask >> i) & 1) {
                cnt++;
                int leaf = (n - m + 1) + i;
                income += val[leaf];
                // 向上点亮通往根节点 1 的路径
                int curr = leaf;
                while (curr != 1) {
                    if (edge_used[curr]) break;
                    edge_used[curr] = true;
                    curr = parent_node[curr];
                }
            }
        }

        ll cost = 0;
        for (int i = 2; i <= n; ++i) {
            if (edge_used[i]) {
                cost += parent_edge_cost[i];
            }
        }

        if (income >= cost) {
            ans = max(ans, cnt);
        }
    }

    cout << ans << "\n";
    return 0;
}
