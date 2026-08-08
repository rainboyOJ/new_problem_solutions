// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
int s, t;
vector<int> g[MAXN];
vector<int> rg[MAXN];

bool can_reach_t[MAXN];
bool safe_node[MAXN];
int dista[MAXN];

// 暴力做法仍然先按定义筛点，只是直接用 vector 存图，适合小数据阅读。
void mark_can_reach_t() {
    queue<int> q;
    q.push(t);
    can_reach_t[t] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < (int)rg[u].size(); i++) {
            int v = rg[u][i];
            if (can_reach_t[v]) continue;
            can_reach_t[v] = true;
            q.push(v);
        }
    }
}

void mark_safe_node() {
    for (int u = 1; u <= n; u++) {
        safe_node[u] = true;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (!can_reach_t[v]) {
                safe_node[u] = false;
                break;
            }
        }
    }
}

int bfs_shortest_path() {
    memset(dista, -1, sizeof(dista));
    if (!safe_node[s] || !safe_node[t]) return -1;

    queue<int> q;
    q.push(s);
    dista[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) return dista[u];

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (!safe_node[v]) continue;
            if (dista[v] != -1) continue;
            dista[v] = dista[u] + 1;
            q.push(v);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    cin >> s >> t;

    mark_can_reach_t();
    mark_safe_node();

    cout << bfs_shortest_path() << '\n';
    return 0;
}
