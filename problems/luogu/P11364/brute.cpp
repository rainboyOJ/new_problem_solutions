// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, q;
vector<int> tree[MAXN];
int parent_node[MAXN], depth_node[MAXN];

void dfs_build(int u, int fa) {
    parent_node[u] = fa;
    depth_node[u] = (fa == 0 ? 1 : depth_node[fa] + 1);
    for (int i = 0; i < (int)tree[u].size(); i++) {
        int v = tree[u][i];
        if (v == fa) {
            continue;
        }
        dfs_build(v, u);
    }
}

int lca_pair(int u, int v) {
    while (depth_node[u] > depth_node[v]) {
        u = parent_node[u];
    }
    while (depth_node[v] > depth_node[u]) {
        v = parent_node[v];
    }
    while (u != v) {
        u = parent_node[u];
        v = parent_node[v];
    }
    return u;
}

int lca_interval(int l, int r) {
    int cur = l;
    for (int i = l + 1; i <= r; i++) {
        cur = lca_pair(cur, i);
    }
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs_build(1, 0);

    cin >> q;
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;

        int ans = 0;
        for (int left = l; left <= r; left++) {
            for (int right = left + k - 1; right <= r; right++) {
                int x = lca_interval(left, right);
                ans = max(ans, depth_node[x]);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
