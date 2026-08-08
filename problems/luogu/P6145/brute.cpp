// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m, c;
int start_day[MAXN];

struct Edge {
    int from, w;
};

vector<Edge> pre[MAXN]; // pre[i] : 所有指向 i 的前驱边

// 暴力枚举所有能影响 u 的前驱链，返回 u 的最早可行日期。
int dfs(int u) {
    int best = start_day[u];

    for (Edge e : pre[u]) {
        best = max(best, dfs(e.from) + e.w);
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++) {
        cin >> start_day[i];
        pre[i].clear();
    }

    for (int i = 1; i <= c; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        pre[v].push_back({u, w});
    }

    for (int i = 1; i <= n; i++) {
        cout << dfs(i) << '\n';
    }

    return 0;
}
