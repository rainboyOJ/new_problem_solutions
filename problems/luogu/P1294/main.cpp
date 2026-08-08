#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXS = 1 << 20;

static int dp[MAXS][MAXN];
static vector<pair<int, int>> g[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = 0;
    }

    int ans = 0;
    int full = 1 << n;
    for (int mask = 1; mask < full; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (dp[mask][u] == -1) {
                continue;
            }
            ans = max(ans, dp[mask][u]);
            for (auto [v, w] : g[u]) {
                if ((mask >> v) & 1) {
                    continue;
                }
                int nmask = mask | (1 << v);
                dp[nmask][v] = max(dp[nmask][v], dp[mask][u] + w);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
