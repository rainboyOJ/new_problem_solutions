/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 12:30
 * update_at: 2026-08-05 12:30
 */
// brute.cpp：小数据暴力解，子树用 DFS 收集节点，路径用 DFS 找路，逐个取异或最大值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, q;
int val[MAXN];
vector<int> g[MAXN];
int parent_node[MAXN];   // 每个节点的父节点（根为 0）

vector<int> path_nodes;

// 求父节点数组
void dfs_parent(int u, int f) {
    parent_node[u] = f;
    for (int v : g[u])
        if (v != f) dfs_parent(v, u);
}

// 收集 u 的子树节点（不经过父节点）
void collect_subtree(int u, int f) {
    path_nodes.push_back(u);
    for (int v : g[u])
        if (v != f) collect_subtree(v, u);
}

// 找 x 到 y 的路径节点，找到返回 true
bool find_path(int u, int target, int f) {
    path_nodes.push_back(u);
    if (u == target) return true;
    for (int v : g[u])
        if (v != f && find_path(v, target, u)) return true;
    path_nodes.pop_back();
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_parent(1, 0);

    for (int t = 0; t < q; t++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, z;
            cin >> x >> z;
            path_nodes.clear();
            collect_subtree(x, parent_node[x]);   // 排除父节点，只收集真子树
            int ans = 0;
            for (int u : path_nodes) ans = max(ans, val[u] ^ z);
            cout << ans << '\n';
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            path_nodes.clear();
            find_path(x, y, 0);
            int ans = 0;
            for (int u : path_nodes) ans = max(ans, val[u] ^ z);
            cout << ans << '\n';
        }
    }

    return 0;
}
