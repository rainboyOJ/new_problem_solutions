#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, V;
    cin >> N >> V;
    // dp[j] 表示容量为 j 时的最大价值。
    vector<int> dp(V + 1, 0);
    for (int i = 0; i < N; i++) {
        int K;
        cin >> K;                        // 函数的关键点数量
        vector<pair<int, int>> points(K);
        for (int j = 0; j < K; j++)
            cin >> points[j].first >> points[j].second;

        // val[x] 表示该泛化物品消耗容量 x 时获得的价值（分段线性）。
        vector<int> val(V + 1, 0);
        for (int x = 0; x <= V; x++) {
            if (x <= points[0].first) {
                val[x] = points[0].second;
            } else if (x >= points.back().first) {
                val[x] = points.back().second;
            } else {
                for (int j = 0; j < K - 1; j++) {
                    int x1 = points[j].first, y1 = points[j].second;
                    int x2 = points[j + 1].first, y2 = points[j + 1].second;
                    if (x1 <= x && x <= x2) {
                        double t = (double)(x - x1) / (x2 - x1);
                        val[x] = (int)(y1 + t * (y2 - y1));
                        break;
                    }
                }
            }
        }

        // 0/1 背包倒序枚举容量，尝试分配给当前物品不同容量 x。
        for (int j = V; j >= 0; j--)
            for (int x = 0; x <= j; x++)
                dp[j] = max(dp[j], dp[j - x] + val[x]);
    }
    cout << dp[V] << '\n';
    return 0;
}
