#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
// dp[j][k] 表示费用1容量为 j、费用2容量为 k 时的最大价值。
int dp[maxn][maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, V, M;
    cin >> N >> V >> M;
    for (int i = 0; i < N; i++) {
        int v, w, p;
        cin >> v >> w >> p;                 // 费用1、费用2、价值
        // 二维费用 0/1 背包：两维都倒序，保证每件物品只选一次。
        for (int j = V; j >= v; j--)
            for (int k = M; k >= w; k--)
                dp[j][k] = max(dp[j][k], dp[j - v][k - w] + p);
    }
    cout << dp[V][M] << '\n';
    return 0;
}
