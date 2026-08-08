#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> g;
static vector<int> vis;
static vector<int> dfs_order;
static vector<int> bfs_order;

void dfs(int u) {
    vis[u] = 1;
    dfs_order.push_back(u);
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

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

    vis.assign(n + 1, 0);
    dfs(1);
    for (int x : dfs_order) {
        cout << x << ' ';
    }
    cout << '\n';

    fill(vis.begin(), vis.end(), 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfs_order.push_back(u);
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }

    for (int x : bfs_order) {
        cout << x << ' ';
    }
    cout << '\n';
    return 0;
}
