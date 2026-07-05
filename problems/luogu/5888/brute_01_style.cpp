// brute_01_style.cpp：选择序列风格暴力，把每一轮传给谁看成一次选择。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int MAXM = 205;
const int MOD = 998244353;

int n, m, k;
bool ban_edge[MAXN][MAXN];
int memo[MAXM][MAXN];
bool vis[MAXM][MAXN];

// dfs_pass(step, u)：已经传了 step 次，球在 u 手中，继续枚举下一轮传给谁。
int dfs_pass(int step, int u) {
    if (step == m) {
        return u == 1;
    }

    if (vis[step][u]) {
        return memo[step][u];
    }
    vis[step][u] = true;

    int ways = 0;
    for (int v = 1; v <= n; v++) {
        if (v == u || ban_edge[u][v]) {
            continue;
        }
        ways += dfs_pass(step + 1, v);
        if (ways >= MOD) {
            ways -= MOD;
        }
    }

    memo[step][u] = ways;
    return ways;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            ban_edge[a][b] = true;
        }
    }

    cout << dfs_pass(0, 1) << '\n';
    return 0;
}
