// brute.cpp：直接在“游戏之间”的图上建边，再求强连通分量。
// 如果一个游戏所在的强连通分量大小大于 1，或者自己有自环，
// 那么它就可能在某条游玩顺序里被玩两次。
#include <bits/stdc++.h>
using namespace std;

int t;
int n;
vector<int> w, e_val;
vector< vector<int> > g, rg;
vector<int> order, scc_id, scc_size;
vector<char> vis, self_loop;

void dfs1(int u) {
    vis[u] = 1;
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!vis[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
}

void dfs2(int u, int color) {
    scc_id[u] = color;
    scc_size[color]++;
    for (size_t i = 0; i < rg[u].size(); i++) {
        int v = rg[u][i];
        if (scc_id[v] == 0) {
            dfs2(v, color);
        }
    }
}

int solve_case() {
    cin >> n;

    w.assign(n + 1, 0);
    e_val.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> e_val[i];
    }

    g.assign(n + 1, vector<int>());
    rg.assign(n + 1, vector<int>());
    self_loop.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (w[j] % e_val[i] == 0) {
                g[i].push_back(j);
                rg[j].push_back(i);
                if (i == j) {
                    self_loop[i] = 1;
                }
            }
        }
    }

    vis.assign(n + 1, 0);
    order.clear();
    order.reserve(n);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    scc_id.assign(n + 1, 0);
    scc_size.assign(n + 1, 0);

    int scc_cnt = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (scc_id[u] == 0) {
            scc_cnt++;
            dfs2(u, scc_cnt);
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (scc_size[scc_id[i]] > 1 || self_loop[i]) {
            answer++;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cout << solve_case() << '\n';
    }

    return 0;
}
