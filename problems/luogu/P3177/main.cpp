#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

struct Edge {
    int to;
    int w;
};

int n, k_need;
vector<Edge> g[MAXN];
int sz[MAXN];
long long dp[MAXN][MAXN];

void dfs(int u, int fa) {
    sz[u] = 1;
    dp[u][0] = 0;
    dp[u][1] = 0;

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        int w = g[u][i].w;
        if (v == fa) {
            continue;
        }

        dfs(v, u);

        static long long tmp[MAXN];
        int upper = min(k_need, sz[u] + sz[v]);
        for (int j = 0; j <= upper; j++) {
            tmp[j] = -(1LL << 60);
        }

        for (int a = 0; a <= min(k_need, sz[u]); a++) {
            for (int b = 0; b <= min(k_need - a, sz[v]); b++) {
                long long add = 0;

                // 黑点对：一边在 v 子树，一边不在 v 子树。
                add += 1LL * b * (k_need - b) * w;

                // 白点对：一边在 v 子树，一边不在 v 子树。
                int white_in_v = sz[v] - b;
                int white_out_v = (n - k_need) - white_in_v;
                add += 1LL * white_in_v * white_out_v * w;

                long long cand = dp[u][a] + dp[v][b] + add;
                if (cand > tmp[a + b]) {
                    tmp[a + b] = cand;
                }
            }
        }

        sz[u] += sz[v];
        for (int j = 0; j <= min(k_need, sz[u]); j++) {
            dp[u][j] = tmp[j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k_need;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        for (int j = 0; j <= k_need; j++) {
            dp[i][j] = -(1LL << 60);
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dfs(1, 0);
    cout << dp[1][k_need] << '\n';
    return 0;
}
