#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const long long MOD = 1000000007LL;

int n, k;
int fixed_color[MAXN];
int color_arr[MAXN];
int adj[MAXN][MAXN];
long long ans;

void dfs(int u) {
    if (u > n) {
        ans = (ans + 1) % MOD;
        return;
    }

    for (int c = 1; c <= 3; c++) {
        if (fixed_color[u] != 0 && fixed_color[u] != c) {
            continue;
        }

        bool ok = true;
        for (int v = 1; v < u; v++) {
            if (adj[u][v] && color_arr[v] == c) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }

        color_arr[u] = c;
        dfs(u + 1);
        color_arr[u] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个小数据精确暴力：
    // 直接枚举每个点的颜色，再检查是否满足相邻点不同色。
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        fixed_color[i] = 0;
        color_arr[i] = 0;
        for (int j = 1; j <= n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    for (int i = 1; i <= k; i++) {
        int u, c;
        cin >> u >> c;
        fixed_color[u] = c;
    }

    ans = 0;
    dfs(1);
    cout << ans % MOD << '\n';
    return 0;
}
