#include <bits/stdc++.h>
using namespace std;

const int MAXN = 6005;

int n;
int happy[MAXN];
vector<int> children[MAXN];
bool has_parent[MAXN];
int dp[MAXN][2]; // dp[u][0]：不选 u 的最大快乐值；dp[u][1]：选择 u 的最大快乐值。

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> happy[i];
    }

    for (int i = 1; i < n; i++) {
        int child, parent;
        cin >> child >> parent;
        children[parent].push_back(child);
        has_parent[child] = true;
    }
}

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = happy[u];

    for (int i = 0; i < (int)children[u].size(); i++) {
        int v = children[u][i];
        dfs(v);

        // 不选 u 时，孩子 v 可选可不选，取更优。
        dp[u][0] += max(dp[v][0], dp[v][1]);

        // 选择 u 时，直接下属 v 不能参加。
        dp[u][1] += dp[v][0];
    }
}

void solve() {
    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (!has_parent[i]) {
            root = i;
            break;
        }
    }

    dfs(root);
    cout << max(dp[root][0], dp[root][1]) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
