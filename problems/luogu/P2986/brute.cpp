#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

struct Edge {
    int to;
    int w;
};

int n;
long long cows[MAXN];
vector<Edge> g[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：对每个点都做一次最短路/BFS 树上距离统计，直接求总代价。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cows[i];
        g[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    long long ans = (1LL << 62);
    for (int start = 1; start <= n; start++) {
        vector<long long> dist(n + 1, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (size_t i = 0; i < g[u].size(); i++) {
                int v = g[u][i].to;
                if (dist[v] != -1) {
                    continue;
                }
                dist[v] = dist[u] + g[u][i].w;
                q.push(v);
            }
        }

        long long cost = 0;
        for (int i = 1; i <= n; i++) {
            cost += cows[i] * dist[i];
        }
        ans = min(ans, cost);
    }

    cout << ans << '\n';
    return 0;
}
