#include <bits/stdc++.h>
using namespace std;

static vector<pair<int, int>> g[25];
static int vis[25];
static int ans = 0;

void dfs(int u, int dist) {
    ans = max(ans, dist);
    for (auto [v, w] : g[u]) {
        if (vis[v]) {
            continue;
        }
        vis[v] = 1;
        dfs(v, dist + w);
        vis[v] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        vis[i] = 1;
        dfs(i, 0);
    }

    cout << ans << '\n';
    return 0;
}
