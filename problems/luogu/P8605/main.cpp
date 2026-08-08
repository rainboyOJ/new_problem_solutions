#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> deg(n + 1, 0);
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v;
        ++deg[edges[i].u];
        ++deg[edges[i].v];
    }

    long long ans = 0;
    for (const auto &e : edges) {
        ans += 1LL * (deg[e.u] - 1) * (deg[e.v] - 1);
        ans += 1LL * (deg[e.v] - 1) * (deg[e.u] - 1);
    }

    cout << ans << '\n';
    return 0;
}
