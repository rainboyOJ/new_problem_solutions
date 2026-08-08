#include <bits/stdc++.h>
using namespace std;

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

    vector<pair<int, int>> query(q);
    int maxL = 0;
    for (int i = 0; i < q; ++i) {
        cin >> query[i].first >> query[i].second;
        maxL = max(maxL, query[i].second);
    }

    vector<vector<int>> can(maxL + 1, vector<int>(n + 1, 0));
    can[0][1] = 1;

    for (int step = 1; step <= maxL; ++step) {
        for (int u = 1; u <= n; ++u) {
            if (!can[step - 1][u]) {
                continue;
            }
            for (int v : g[u]) {
                can[step][v] = 1;
            }
        }
    }

    for (auto [a, L] : query) {
        cout << (can[L][a] ? "Yes" : "No") << '\n';
    }
    return 0;
}
