#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> g;

bool disconnected_after_remove(int n, int x, int y, int ban) {
    vector<int> vis(n + 1, 0);
    queue<int> q;
    q.push(x);
    vis[x] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (v == ban || vis[v]) {
                continue;
            }
            vis[v] = 1;
            q.push(v);
        }
    }

    return !vis[y];
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
        g[v].push_back(u);
    }

    int x, y;
    cin >> x >> y;
    int ans = 0;
    for (int z = 1; z <= n; ++z) {
        if (z == x || z == y) {
            continue;
        }
        if (disconnected_after_remove(n, x, y, z)) {
            ++ans;
        }
    }

    cout << ans << '\n';
    return 0;
}
