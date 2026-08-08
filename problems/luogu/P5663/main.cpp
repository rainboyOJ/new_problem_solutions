#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<array<int, 2>> dist(n + 1, {INF, INF});
    queue<pair<int, int>> qu;
    dist[1][0] = 0;
    qu.push({1, 0});

    // 分层图 BFS：状态 (u, p) 表示到点 u、步数奇偶为 p 的最短长度。
    while (!qu.empty()) {
        auto [u, p] = qu.front();
        qu.pop();
        for (int v : g[u]) {
            int np = p ^ 1;
            if (dist[v][np] != INF) {
                continue;
            }
            dist[v][np] = dist[u][p] + 1;
            qu.push({v, np});
        }
    }

    int min_even_self = (g[1].empty() ? INF : 2);

    while (q--) {
        int a, L;
        cin >> a >> L;
        int p = L & 1;
        int need = dist[a][p];
        if (a == 1 && p == 0) {
            need = min_even_self;
        }
        if (need <= L) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
