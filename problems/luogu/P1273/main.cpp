/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:32
 * update_at: 2026-10-23 23:32
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 3005;

struct Edge {
    int to;
    ll w;
};

ll n, m;
vector<Edge> g[MAXN];
ll val[MAXN];
ll dp[MAXN][MAXN];
ll sz[MAXN]; // 子树中用户终端（叶子）的数量

void dfs(int u) {
    if (u > n - m) {
        // 用户终端
        sz[u] = 1;
        dp[u][0] = 0;
        dp[u][1] = val[u];
        return;
    }

    dp[u][0] = 0;
    sz[u] = 0;

    for (const auto &e : g[u]) {
        int v = e.to;
        ll w = e.w;
        dfs(v);

        // 树上背包合并：从大到小枚举以防止重复计算
        for (ll j = sz[u] + sz[v]; j >= 0; --j) {
            for (ll k = 1; k <= sz[v] && k <= j; ++k) {
                if (dp[u][j - k] != -INF && dp[v][k] != -INF) {
                    dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k] - w);
                }
            }
        }
        sz[u] += sz[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n - m; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int to;
            ll cost;
            cin >> to >> cost;
            g[i].push_back({to, cost});
        }
    }

    for (int i = n - m + 1; i <= n; ++i) {
        cin >> val[i];
    }

    // 初始化 dp 数组为极小值
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = -INF;
        }
    }

    dfs(1);

    // 寻找在根节点净收益 >= 0 的最大用户数
    for (ll j = m; j >= 0; --j) {
        if (dp[1][j] >= 0) {
            cout << j << "\n";
            break;
        }
    }

    return 0;
}
