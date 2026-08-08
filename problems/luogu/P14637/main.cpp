#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8005;

int n, m;
vector<int> sons[MAXN];
int siz[MAXN], height_len[MAXN], heavy_son[MAXN];

int f[MAXN];          // 固定当前 UM 时，f[u] 表示子树 u 的最优值
int g[MAXN][2];       // g[u][0] 是当前 UM，g[u][1] 是 UM+1
int outside_sum[MAXN];
int delta[MAXN];
int pool[MAXN];
int pool_len;
int *best_same_depth[MAXN];
int current_um;

void update_max(int &x, int y) {
    if (y > x) {
        x = y;
    }
}

void dfs_prepare(int u) {
    siz[u] = 1;
    height_len[u] = 1;
    heavy_son[u] = 0;

    for (int i = 0; i < (int)sons[u].size(); i++) {
        int v = sons[u][i];
        dfs_prepare(v);
        siz[u] += siz[v];
        if (height_len[v] + 1 > height_len[u]) {
            height_len[u] = height_len[v] + 1;
            heavy_son[u] = v;
        }
    }
}

void dfs_dp(int u) {
    int child_f_sum = 0;

    if (best_same_depth[u] == nullptr) {
        best_same_depth[u] = pool + pool_len;
        pool_len += height_len[u];
    }

    if (heavy_son[u] != 0) {
        best_same_depth[heavy_son[u]] = best_same_depth[u] + 1;
    }

    f[u] = current_um * siz[u];
    g[u][0] = current_um * siz[u];

    for (int i = 0; i < (int)sons[u].size(); i++) {
        int v = sons[u][i];
        dfs_dp(v);
        child_f_sum += f[v];
    }

    for (int i = 0; i < (int)sons[u].size(); i++) {
        int v = sons[u][i];
        outside_sum[v] = child_f_sum - f[v];
        update_max(g[u][0], g[v][1] + current_um + outside_sum[v]);
    }

    if (heavy_son[u] != 0) {
        int hv = heavy_son[u];
        delta[u] = delta[hv] + outside_sum[hv];

        for (int i = 0; i < (int)sons[u].size(); i++) {
            int v = sons[u][i];
            if (v == hv) {
                continue;
            }
            for (int d = 1; d <= height_len[v]; d++) {
                int val = best_same_depth[v][d] + outside_sum[v] + delta[v] - delta[u];
                update_max(best_same_depth[u][d + 1], val);
            }
        }
    }

    best_same_depth[u][1] = g[u][0] - delta[u];
    if (height_len[u] >= current_um) {
        int val = best_same_depth[u][current_um] + delta[u] + current_um * (current_um - 1);
        update_max(f[u], val);
    }
}

void solve_case() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        sons[i].clear();
    }

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        sons[p].push_back(i);
    }

    dfs_prepare(1);

    for (int i = 1; i <= n; i++) {
        f[i] = (m + 2) * siz[i];
        g[i][0] = (m + 2) * siz[i];
        g[i][1] = 0;
    }

    for (current_um = m + 1; current_um >= 1; current_um--) {
        pool_len = 0;
        for (int i = 0; i <= n + 2; i++) {
            pool[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            best_same_depth[i] = nullptr;
            delta[i] = 0;
            swap(g[i][0], g[i][1]);
        }

        dfs_dp(1);
    }

    cout << g[1][0] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
