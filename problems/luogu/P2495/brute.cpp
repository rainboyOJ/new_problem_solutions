#include <bits/stdc++.h>
using namespace std;

// brute.cpp：在原树上直接 DP，每次询问 O(n)，用于小数据对拍。

const int MAXN = 505;
const long long INF = (1LL << 60);

struct Edge {
    int to, w;
};

int n, query_count;
vector<Edge> graph_edges[MAXN];
bool is_key[MAXN];

long long dfs_solve(int u, int parent) {
    if (is_key[u]) {
        return INF;
    }

    long long answer = 0;
    for (int i = 0; i < (int)graph_edges[u].size(); i++) {
        int v = graph_edges[u][i].to;
        int w = graph_edges[u][i].w;
        if (v == parent) {
            continue;
        }
        long long child_cost = dfs_solve(v, u);
        if (child_cost > 0) {
            answer += min(child_cost, (long long)w);
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph_edges[u].push_back({v, w});
        graph_edges[v].push_back({u, w});
    }

    cin >> query_count;
    for (int qi = 1; qi <= query_count; qi++) {
        int k;
        cin >> k;
        vector<int> nodes(k);
        for (int i = 0; i < k; i++) {
            cin >> nodes[i];
            is_key[nodes[i]] = true;
        }

        cout << dfs_solve(1, 0) << '\n';

        for (int i = 0; i < k; i++) {
            is_key[nodes[i]] = false;
        }
    }

    return 0;
}
