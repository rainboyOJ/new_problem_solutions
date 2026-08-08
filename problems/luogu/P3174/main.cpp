#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

int n, m;
vector<int> g[MAXN];
int w[MAXN];
int down_val[MAXN];
int ans;

void dfs(int u, int fa) {
    down_val[u] = w[u];

    int best1 = 0;
    int best2 = 0;

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        dfs(v, u);

        int cand = down_val[v];
        if (cand > best1) {
            best2 = best1;
            best1 = cand;
        } else if (cand > best2) {
            best2 = cand;
        }
    }

    down_val[u] = w[u] + best1;
    ans = max(ans, w[u] + best1 + best2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        w[i] = (int) g[i].size() - 1;
    }

    ans = 0;
    dfs(1, 0);

    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }

    // 路径上所有点的 (deg-1) 之和，再补回路径两个端点。
    cout << ans + 2 << '\n';
    return 0;
}
