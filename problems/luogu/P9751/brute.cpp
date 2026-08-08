#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int open;
};

const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, a;
        cin >> u >> v >> a;
        g[u].push_back({v, a});
    }

    vector<vector<long long>> dist(n + 1, vector<long long>(k, INF));
    deque<pair<int, int>> q;
    vector<vector<int>> inq(n + 1, vector<int>(k, 0));
    dist[1][0] = 0;
    q.push_back({1, 0});
    inq[1][0] = 1;

    while (!q.empty()) {
        auto [u, mod] = q.front();
        q.pop_front();
        inq[u][mod] = 0;

        for (const auto &e : g[u]) {
            long long nd = dist[u][mod];
            if (nd < e.open) {
                long long delta = e.open - nd;
                long long t = (delta + k - 1) / k;
                nd += t * 1LL * k;
            }
            ++nd;
            int nmod = nd % k;
            if (nd < dist[e.to][nmod]) {
                dist[e.to][nmod] = nd;
                if (!inq[e.to][nmod]) {
                    inq[e.to][nmod] = 1;
                    q.push_back({e.to, nmod});
                }
            }
        }
    }

    if (dist[n][0] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dist[n][0] << '\n';
    }
    return 0;
}
