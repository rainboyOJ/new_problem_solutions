#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int NEG = -1000000000;

int n, m;
int credit[MAXN];
vector<int> children[MAXN];
int dp[MAXN][MAXN]; // dp[u][j]：在 u 的子树中选 j 门课，并且必须选 u，能得到的最大学分。

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int parent;
        cin >> parent >> credit[i];
        children[parent].push_back(i);
    }
}

void dfs(int u) {
    for (int j = 0; j <= m + 1; j++) {
        dp[u][j] = NEG;
    }

    // 若选择 u，至少占用 1 个名额。虚拟根 0 的学分为 0。
    dp[u][1] = credit[u];

    for (int idx = 0; idx < (int)children[u].size(); idx++) {
        int v = children[u][idx];
        dfs(v);

        // 树上背包：把总名额 j 分一部分 k 给孩子 v 的子树。
        for (int j = m + 1; j >= 1; j--) {
            for (int k = 1; k < j; k++) {
                if (dp[u][j - k] == NEG || dp[v][k] == NEG) {
                    continue;
                }
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
    }
}

void solve() {
    dfs(0);
    cout << dp[0][m + 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
