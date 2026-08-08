#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m, c;
int start_day[MAXN]; // start_day[i] : 第 i 次挤奶最早不能早于哪一天
int dp[MAXN];        // dp[i] : 第 i 次挤奶在满足条件下的最早日期

struct Edge {
    int to, w;
};

struct TopologicalSort {
    int n;
    vector<vector<Edge>> graph;
    vector<int> indeg;

    explicit TopologicalSort(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        graph.assign(n + 1, vector<Edge>());
        indeg.assign(n + 1, 0);
    }

    void add_edge(int u, int v, int w) {
        graph[u].push_back({v, w});
        indeg[v]++;
    }

    vector<int> kahn() {
        queue<int> q;
        vector<int> deg = indeg;
        vector<int> order;

        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (Edge e : graph[u]) {
                int v = e.to;
                deg[v]--;
                if (deg[v] == 0) {
                    q.push(v);
                }
            }
        }

        return order;
    }
};

TopologicalSort topo;

void read_input() {
    cin >> n >> m >> c;
    topo.init(n);

    for (int i = 1; i <= n; i++) {
        cin >> start_day[i];
        dp[i] = start_day[i];
    }

    for (int i = 1; i <= c; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        topo.add_edge(u, v, w);
    }
}

void solve() {
    vector<int> order = topo.kahn();

    for (int u : order) {
        for (Edge e : topo.graph[u]) {
            int v = e.to;
            dp[v] = max(dp[v], dp[u] + e.w);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    for (int i = 1; i <= n; i++) {
        cout << dp[i] << '\n';
    }

    return 0;
}
