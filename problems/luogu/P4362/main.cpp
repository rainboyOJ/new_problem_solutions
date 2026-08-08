#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const long long INF = (1LL << 60);

struct Edge {
    int to;
    int w;
};

int n, m, k_need;
vector<Edge> g[MAXN];
int sz[MAXN];
long long dp[MAXN][MAXN][2];
long long tmp[MAXN][2];

void dfs(int u, int fa) {
    sz[u] = 1;
    for (int i = 0; i <= k_need; i++) {
        dp[u][i][0] = INF;
        dp[u][i][1] = INF;
    }

    // state=0: u 不给大头
    // state=1: u 给大头
    dp[u][0][0] = 0;
    dp[u][1][1] = 0;

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i].to;
        int w = g[u][i].w;
        if (v == fa) {
            continue;
        }

        dfs(v, u);
        int upper = min(k_need, sz[u] + sz[v]);
        for (int j = 0; j <= upper; j++) {
            tmp[j][0] = INF;
            tmp[j][1] = INF;
        }

        for (int a = 0; a <= min(k_need, sz[u]); a++) {
            for (int su = 0; su <= 1; su++) {
                if (dp[u][a][su] >= INF) {
                    continue;
                }
                for (int b = 0; b <= min(k_need - a, sz[v]); b++) {
                    for (int sv = 0; sv <= 1; sv++) {
                        if (dp[v][b][sv] >= INF) {
                            continue;
                        }

                        long long add = 0;
                        if (m == 2) {
                            // 两个头时，同色边一定会被吃掉。
                            if (su == sv) {
                                add = w;
                            }
                        } else {
                            // 至少三个头时，只要两端都不给大头，就总能用不同普通头把边砍断。
                            // 因此只有两端都给大头时，这条边才一定要被吃掉。
                            if (su == 1 && sv == 1) {
                                add = w;
                            }
                        }

                        long long cand = dp[u][a][su] + dp[v][b][sv] + add;
                        if (cand < tmp[a + b][su]) {
                            tmp[a + b][su] = cand;
                        }
                    }
                }
            }
        }

        sz[u] += sz[v];
        if (sz[u] > k_need) {
            sz[u] = k_need;
        }
        for (int j = 0; j <= sz[u]; j++) {
            dp[u][j][0] = tmp[j][0];
            dp[u][j][1] = tmp[j][1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k_need;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    dfs(1, 0);
    cout << dp[1][k_need][1] << '\n';
    return 0;
}
