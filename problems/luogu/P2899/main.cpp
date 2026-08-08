#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int INF = 1e9;

vector<int> g[MAXN];
int n;
int dp[MAXN][3];

void dfs(int u, int fa) {
    dp[u][0] = 1;   // u 放塔
    dp[u][1] = 0;   // u 不放塔，且已被儿子覆盖
    dp[u][2] = 0;   // u 不放塔，等待父亲覆盖

    int sum_min_01 = 0;
    bool has_child = false;
    int extra = INF;

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        has_child = true;
        dfs(v, u);

        dp[u][0] += min(dp[v][0], min(dp[v][1], dp[v][2]));
        dp[u][2] += min(dp[v][0], dp[v][1]);

        int best01 = min(dp[v][0], dp[v][1]);
        sum_min_01 += best01;
        extra = min(extra, dp[v][0] - best01);
    }

    if (!has_child) {
        dp[u][1] = INF;
        dp[u][2] = 0;
        return;
    }

    // 至少要有一个儿子放塔，才能覆盖 u。
    dp[u][1] = sum_min_01 + extra;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    cout << min(dp[1][0], dp[1][1]) << '\n';
    return 0;
}
