/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:27
 * update_at: 2026-08-12 22:27
 */
// main.cpp：换根 DP 求树上所有点到某点的距离和最小值（P1395 会议）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
vector<int> g[MAXN];      // 树的邻接表
int parent_node[MAXN];    // parent_node[u]：以 1 为根时 u 的父亲，根的父节点为 0
int depth_arr[MAXN];      // depth_arr[u]：以 1 为根时 u 的深度
int order_arr[MAXN];      // order_arr[]：BFS 遍历序，第 1 个是根 1
int order_cnt;            // BFS 访问到的节点个数
int subtree_size[MAXN];   // subtree_size[u]：以 1 为根时 u 子树内的节点数
long long dist_sum[MAXN]; // dist_sum[u]：所有节点到 u 的距离和

// BFS 求遍历序、父亲、深度，并顺带求 dist_sum[1]（所有点深度之和）。
void bfs_root() {
    queue<int> q;
    q.push(1);
    parent_node[1] = 0;
    depth_arr[1] = 0;
    order_cnt = 0;
    dist_sum[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order_arr[++order_cnt] = u;
        dist_sum[1] += depth_arr[u];

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_node[u]) continue;
            parent_node[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            q.push(v);
        }
    }
}

// 逆序遍历序，自底向上累加每棵子树的大小。
void calc_subtree_size() {
    for (int i = 1; i <= n; i++) subtree_size[i] = 1;
    for (int i = order_cnt; i >= 1; i--) {
        int u = order_arr[i];
        if (parent_node[u] != 0) {
            subtree_size[parent_node[u]] += subtree_size[u];
        }
    }
}

// 换根 DP：根从 u 移到儿子 v 时，用公式推出 v 的距离和。
void reroot_dp() {
    for (int i = 1; i <= order_cnt; i++) {
        int u = order_arr[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (parent_node[v] != u) continue; // 只走父亲 -> 儿子方向

            // 换根公式：v 子树内 subtree_size[v] 个点距离各 -1，
            // 其余 n - subtree_size[v] 个点距离各 +1，
            // 所以 dist_sum[v] = dist_sum[u] + n - 2 * subtree_size[v]。
            dist_sum[v] = dist_sum[u] + (long long)n - 2LL * subtree_size[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs_root();
    calc_subtree_size();
    reroot_dp();

    // 距离和取最小；距离和相等时保留编号最小的点（只严格小于才更新）。
    int best_node = 1;
    long long best_sum = dist_sum[1];
    for (int i = 2; i <= n; i++) {
        if (dist_sum[i] < best_sum) {
            best_sum = dist_sum[i];
            best_node = i;
        }
    }

    cout << best_node << " " << best_sum << "\n";

    return 0;
}
