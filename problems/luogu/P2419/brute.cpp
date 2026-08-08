// brute.cpp：对每头牛分别做两次 DFS。
// 一次找它能赢谁，一次找谁能赢它，再判断和所有牛的相对强弱是否都已知。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 5;

int n, m;
vector<int> g[MAXN];
vector<int> rg[MAXN];
bool vis[MAXN];

void dfs(const vector<int> graph[], int u) {
    vis[u] = true;
    for (size_t i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if (!vis[v]) {
            dfs(graph, v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        g[i].clear();
        rg[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    int answer = 0;

    for (int i = 1; i <= n; i++) {
        int beat_cnt = 0;
        int lose_cnt = 0;

        memset(vis, 0, sizeof(vis));
        dfs(g, i);
        for (int j = 1; j <= n; j++) {
            if (j != i && vis[j]) {
                beat_cnt++;
            }
        }

        memset(vis, 0, sizeof(vis));
        dfs(rg, i);
        for (int j = 1; j <= n; j++) {
            if (j != i && vis[j]) {
                lose_cnt++;
            }
        }

        if (beat_cnt + lose_cnt == n - 1) {
            answer++;
        }
    }

    cout << answer << '\n';

    return 0;
}
