#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> g;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
    }

    vector<int> vis(n + 1, 0);
    vector<int> dfs_order;
    dfs_order.reserve(n);

    // 非递归 DFS，避免 1e5 深度时爆栈。
    stack<int> st;
    st.push(1);
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        dfs_order.push_back(u);
        for (int i = (int)g[u].size() - 1; i >= 0; --i) {
            int v = g[u][i];
            if (!vis[v]) {
                st.push(v);
            }
        }
    }

    for (int x : dfs_order) {
        cout << x << ' ';
    }
    cout << '\n';

    fill(vis.begin(), vis.end(), 0);
    queue<int> q;
    vector<int> bfs_order;
    bfs_order.reserve(n);

    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfs_order.push_back(u);
        for (int v : g[u]) {
            if (vis[v]) {
                continue;
            }
            vis[v] = 1;
            q.push(v);
        }
    }

    for (int x : bfs_order) {
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}
