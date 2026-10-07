/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:09
 * update_at: 2026-10-06 10:09
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const ll INF = (ll)1e18;

ll adj[MAXN][MAXN];     // 邻接矩阵，adj[i][j] 表示农场 i 到农场 j 的距离
ll min_cost[MAXN];      // 未加入树的农场到当前树的最小边权
bool in_tree[MAXN];     // 标记农场是否已加入最小生成树

// 在稠密完全图上用 O(n^2) Prim 算法求最小生成树边权和
ll prim_mst(int n) {
    for (int i = 1; i <= n; ++i) {
        min_cost[i] = INF;
        in_tree[i] = false;
    }
    min_cost[1] = 0; // 从农场 1 开始构建生成树

    ll total = 0;
    for (int round = 1; round <= n; ++round) {
        // 在未加入树的农场中选出到树距离最小的点 u
        int u = -1;
        for (int i = 1; i <= n; ++i) {
            if (!in_tree[i] && (u == -1 || min_cost[i] < min_cost[u])) {
                u = i;
            }
        }

        in_tree[u] = true;
        total += min_cost[u];

        // 用 u 到其它未加入树农场的边松弛最小距离
        for (int v = 1; v <= n; ++v) {
            if (!in_tree[v] && adj[u][v] < min_cost[v]) {
                min_cost[v] = adj[u][v];
            }
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> adj[i][j];
        }
    }

    cout << prim_mst(n) << "\n";
    return 0;
}
