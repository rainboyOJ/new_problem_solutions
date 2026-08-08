// brute.cpp：直接把每个格子看成有向图里的一个点，再做强连通分量。
// 这版更接近题目的原始图模型，适合帮助理解和小数据对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXR = 35;
const int MAXC = 35;

int w, l;
int h[MAXR][MAXC];

vector<int> g[1005], rg[1005];
bool vis[1005];
int scc_id[1005];
vector<int> order;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool in_board(int x, int y) {
    return x >= 1 && x <= l && y >= 1 && y <= w;
}

int id(int x, int y) {
    return (x - 1) * w + y;
}

void dfs1(int u) {
    vis[u] = true;
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
    for (size_t i = 0; i < rg[u].size(); i++) {
        int v = rg[u][i];
        if (scc_id[v] == 0) {
            dfs2(v, color);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> l;
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> h[i][j];
        }
    }

    int tot = w * l;
    for (int i = 1; i <= tot; i++) {
        g[i].clear();
        rg[i].clear();
        vis[i] = false;
        scc_id[i] = 0;
    }
    order.clear();

    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= w; j++) {
            int u = id(i, j);
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (!in_board(ni, nj)) {
                    continue;
                }

                if (h[ni][nj] <= h[i][j]) {
                    int v = id(ni, nj);
                    g[u].push_back(v);
                    rg[v].push_back(u);
                }
            }
        }
    }

    for (int i = 1; i <= tot; i++) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    int scc_cnt = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (scc_id[u] == 0) {
            scc_cnt++;
            dfs2(u, scc_cnt);
        }
    }

    if (scc_cnt == 1) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> indeg(scc_cnt + 1, 0);
    vector<int> outdeg(scc_cnt + 1, 0);

    for (int u = 1; u <= tot; u++) {
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            int su = scc_id[u];
            int sv = scc_id[v];
            if (su != sv) {
                outdeg[su] = 1;
                indeg[sv] = 1;
            }
        }
    }

    int source_cnt = 0;
    int sink_cnt = 0;

    for (int i = 1; i <= scc_cnt; i++) {
        if (indeg[i] == 0) {
            source_cnt++;
        }
        if (outdeg[i] == 0) {
            sink_cnt++;
        }
    }

    cout << max(source_cnt, sink_cnt) << '\n';

    return 0;
}
