// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n, m, s, t, t0;

struct Edge {
    int to, w;
};

vector<Edge> graph[MAXN];
long long path_cnt;
long long total_len;

// 直接枚举所有从 s 到 t 的路径。
void dfs(int u, long long len) {
    if (u == t) {
        path_cnt++;
        total_len += len;
        return;
    }

    for (Edge e : graph[u]) {
        dfs(e.to, len + e.w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> t >> t0;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    path_cnt = 0;
    total_len = 0;
    dfs(s, 0);

    cout << total_len + (path_cnt - 1) * t0 << '\n';
    return 0;
}
