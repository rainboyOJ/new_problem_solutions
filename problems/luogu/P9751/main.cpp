#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int open;
};

struct Node {
    long long dist;
    int u;
    int mod;
    bool operator<(const Node &other) const {
        return dist > other.dist;
    }
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
    priority_queue<Node> pq;
    dist[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        long long d = cur.dist;
        int u = cur.u;
        int mod = cur.mod;
        if (d != dist[u][mod]) {
            continue;
        }

        for (const auto &e : g[u]) {
            long long nd = d;
            if (nd < e.open) {
                long long delta = e.open - nd;
                long long t = (delta + k - 1) / k;
                nd += t * 1LL * k;
            }
            ++nd;
            int nmod = nd % k;
            if (nd < dist[e.to][nmod]) {
                dist[e.to][nmod] = nd;
                pq.push({nd, e.to, nmod});
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
