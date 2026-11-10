/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:39
 * update_at: 2026-11-10 23:39
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
const ll INF = 1e18;
const int MAXN = 2005;

int n, m;
string problem_type;
ll p[MAXN];
vector<int> tree[MAXN];

int limit_node[2];
int limit_state[2];

ll dp[MAXN][2];

void dfs(int u, int fa) {
    dp[u][0] = 0;
    dp[u][1] = p[u];

    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        if (dp[u][0] < INF) {
            if (dp[v][1] >= INF) dp[u][0] = INF;
            else dp[u][0] += dp[v][1];
        }
        if (dp[u][1] < INF) {
            ll best_v = min(dp[v][0], dp[v][1]);
            if (best_v >= INF) dp[u][1] = INF;
            else dp[u][1] += best_v;
        }
    }

    // 检查限制
    for (int k = 0; k < 2; ++k) {
        if (u == limit_node[k]) {
            if (limit_state[k] == 0) {
                dp[u][1] = INF; // 不能选
            } else {
                dp[u][0] = INF; // 必须选
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> problem_type)) return 0;

    for (int i = 1; i <= n; ++i) cin >> p[i];

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    while (m--) {
        int a, x, b, y;
        cin >> a >> x >> b >> y;
        limit_node[0] = a; limit_state[0] = x;
        limit_node[1] = b; limit_state[1] = y;

        dfs(1, 0);
        ll ans = min(dp[1][0], dp[1][1]);
        if (ans >= INF) cout << -1 << "\n";
        else cout << ans << "\n";
    }

    return 0;
}
