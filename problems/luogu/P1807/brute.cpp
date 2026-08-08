#include <bits/stdc++.h>
using namespace std;

const long long NEG_INF = -(1LL << 60);

int n, m;
vector<pair<int, long long>> g[25];
long long best_answer = NEG_INF;

// brute.cpp：小数据暴力解，枚举从 1 出发到 n 的所有路径。
void dfs(int u, long long dist) {
    if (u == n) {
        best_answer = max(best_answer, dist);
        return;
    }

    for (auto edge : g[u]) {
        int v = edge.first;
        long long w = edge.second;
        dfs(v, dist + w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    dfs(1, 0);
    if (best_answer == NEG_INF) {
        cout << -1 << '\n';
    } else {
        cout << best_answer << '\n';
    }

    return 0;
}
