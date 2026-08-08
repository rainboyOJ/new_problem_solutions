#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据逐层爬父亲求 LCA，用来辅助对拍。

const int MAXN = 1005;

int n, m, root;
vector<int> graph_edges[MAXN];
int parent_node[MAXN];
int depth_node[MAXN];

void dfs(int u, int parent) {
    parent_node[u] = parent;
    for (int i = 0; i < (int)graph_edges[u].size(); i++) {
        int v = graph_edges[u][i];
        if (v == parent) {
            continue;
        }
        depth_node[v] = depth_node[u] + 1;
        dfs(v, u);
    }
}

int lca_brute(int x, int y) {
    while (depth_node[x] > depth_node[y]) {
        x = parent_node[x];
    }
    while (depth_node[y] > depth_node[x]) {
        y = parent_node[y];
    }
    while (x != y) {
        x = parent_node[x];
        y = parent_node[y];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> root;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph_edges[u].push_back(v);
        graph_edges[v].push_back(u);
    }

    depth_node[root] = 1;
    dfs(root, 0);

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        cout << lca_brute(x, y) << '\n';
    }

    return 0;
}
