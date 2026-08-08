#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n, m;
int cost_[MAXN]; // cost_[i] : 第 i 头奶牛单独挤奶需要的时间
int dp[MAXN];    // dp[i] : 完成第 i 头奶牛的最早结束时间

struct TopologicalSort {
    int n;
    vector<vector<int>> graph;
    vector<int> indeg;

    explicit TopologicalSort(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        graph.assign(n + 1, vector<int>());
        indeg.assign(n + 1, 0);
    }

    void add_edge(int u, int v) {
        graph[u].push_back(v);
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

            for (int v : graph[u]) {
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
    cin >> n >> m;
    topo.init(n);

    for (int i = 1; i <= n; i++) {
        cin >> cost_[i];
        dp[i] = cost_[i];
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        topo.add_edge(u, v);
    }
}

int solve() {
    vector<int> order = topo.kahn();
    int answer = 0;

    for (int u : order) {
        answer = max(answer, dp[u]);
        for (int v : topo.graph[u]) {
            dp[v] = max(dp[v], dp[u] + cost_[v]);
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << solve() << '\n';

    return 0;
}
