/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-08-12 22:30
 */
// brute.cpp：小数据暴力解，每条路径沿父链逐边 +1，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
vector<int> g[MAXN]; // 邻接表存树

int depth[MAXN];
int parent[MAXN];    // parent[x] 表示 x 的父节点，边 (x, parent[x]) 由 x 代表
int edge_val[MAXN];  // edge_val[x] 表示边 (x, parent[x]) 被覆盖的次数

// 朴素 BFS 求父节点与深度。
void build_tree(int root) {
    vector<int> order;
    order.push_back(root);
    depth[root] = 1;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }
}

// 朴素 LCA：两个点交替沿父链一步一步向上爬。
int naive_lca(int a, int b) {
    while (depth[a] > depth[b]) {
        a = parent[a];
    }
    while (depth[b] > depth[a]) {
        b = parent[b];
    }
    while (a != b) {
        a = parent[a];
        b = parent[b];
    }
    return a;
}

// 路径 u->v 上的每条边 +1：从 u 爬到 lca，再从 v 爬到 lca，逐边加一。
void path_add(int u, int v) {
    int c = naive_lca(u, v);
    while (u != c) {
        edge_val[u]++; // 边 (u, parent[u]) 在路径上
        u = parent[u];
    }
    while (v != c) {
        edge_val[v]++;
        v = parent[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_tree(1);

    while (m--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'P') {
            path_add(a, b);
        } else {
            // Q：a、b 是一条边的两个端点，深的一端代表这条边。
            int child = (depth[a] > depth[b]) ? a : b;
            cout << edge_val[child] << '\n';
        }
    }

    return 0;
}
