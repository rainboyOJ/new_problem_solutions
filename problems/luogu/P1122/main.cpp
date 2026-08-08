#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16005;

int n;
int beauty[MAXN];
vector<int> graph_edges[MAXN];
int dp[MAXN]; // dp[u] 表示必须保留 u，且只在 u 子树中选择连通块时的最大美丽和。
int answer;

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> beauty[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph_edges[u].push_back(v);
        graph_edges[v].push_back(u);
    }
}

void dfs(int u, int parent) {
    dp[u] = beauty[u];

    for (int i = 0; i < (int)graph_edges[u].size(); i++) {
        int v = graph_edges[u][i];
        if (v == parent) {
            continue;
        }
        dfs(v, u);

        // 子树贡献为正时才接到 u 上；负贡献剪掉更优。
        if (dp[v] > 0) {
            dp[u] += dp[v];
        }
    }

    answer = max(answer, dp[u]);
}

void solve() {
    answer = beauty[1];
    dfs(1, 0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
