#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
const int MAXP = 305;
const int INF = 0x3f3f3f3f;

int v, p;
int x[MAXN];
int cost[MAXN][MAXN];
int dp[MAXP][MAXN];

// 分治优化：
// 计算 dp[layer][l..r]，最优决策点在 [opt_l, opt_r] 中。
void solve_layer(int layer, int l, int r, int opt_l, int opt_r) {
    if (l > r) {
        return;
    }

    int mid = (l + r) >> 1;
    int best_k = -1;
    dp[layer][mid] = INF;

    int right = min(mid - 1, opt_r);
    for (int k = opt_l; k <= right; k++) {
        int val = dp[layer - 1][k] + cost[k + 1][mid];
        if (val < dp[layer][mid]) {
            dp[layer][mid] = val;
            best_k = k;
        }
    }

    solve_layer(layer, l, mid - 1, opt_l, best_k);
    solve_layer(layer, mid + 1, r, best_k, opt_r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> v >> p;
    for (int i = 1; i <= v; i++) {
        cin >> x[i];
    }
    sort(x + 1, x + v + 1);

    // 预处理一段区间只建一个邮局时的最小总代价。
    // 最优邮局位置是中位数点。
    for (int l = v; l >= 1; l--) {
        for (int r = l; r <= v; r++) {
            int mid = (l + r) >> 1;
            cost[l][r] = cost[l][r - 1] + x[r] - x[mid];
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= v; i++) {
        dp[1][i] = cost[1][i];
    }

    for (int layer = 2; layer <= p; layer++) {
        solve_layer(layer, layer, v, layer - 1, v - 1);
    }

    cout << dp[p][v] << '\n';
    return 0;
}
