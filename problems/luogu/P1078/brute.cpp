// brute.cpp：小数据 DFS 枚举所有合法路线。
// 这份代码是严格正确的暴力解，用来帮助理解约束并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXK = 20;
const long long INF = (1LL << 60);

struct Edge {
    int to;
    int w;
};

int n, k, m, s, t;
int culture[MAXN];
bool hate[MAXK][MAXK];
vector<Edge> g[MAXN];
bool learned[MAXK];
long long answer;

void dfs(int u, long long dist) {
    if (dist >= answer) {
        return;
    }

    if (u == t) {
        answer = dist;
        return;
    }

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        int w = g[u][i].w;
        int cv = culture[v];

        if (learned[cv]) {
            continue;
        }

        bool bad = false;
        for (int c = 1; c <= k; c++) {
            if (learned[c] && hate[cv][c]) {
                bad = true;
                break;
            }
        }
        if (bad) {
            continue;
        }

        learned[cv] = true;
        dfs(v, dist + w);
        learned[cv] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> m >> s >> t;

    for (int i = 1; i <= n; i++) {
        cin >> culture[i];
        g[i].clear();
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            cin >> hate[i][j];
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        g[u].push_back({v, d});
        g[v].push_back({u, d});
    }

    for (int i = 1; i <= k; i++) {
        learned[i] = false;
    }
    learned[culture[s]] = true;
    answer = INF;

    dfs(s, 0);

    if (answer == INF) {
        cout << -1 << '\n';
    }
    else {
        cout << answer << '\n';
    }

    return 0;
}
