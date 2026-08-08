#include <bits/stdc++.h>
using namespace std;

const int MAXW = 40005;

int n, W;
// dp[j] 表示容量为 j 时的最大总价值。
int dp[MAXW];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> W;

    for (int i = 1; i <= n; i++) {
        int v, w, m;
        cin >> v >> w >> m;              // 价值 v，重量 w，数量 m

        // 二进制分组优化多重背包：把 m 拆成 1,2,4,... 的包。
        int k = 1;
        while (m > 0) {
            int use = min(k, m);
            int wv = use * w;            // 包的重量
            int vv = use * v;            // 包的价值
            // 每包作为 0/1 背包物品，倒序枚举。
            for (int j = W; j >= wv; j--) {
                dp[j] = max(dp[j], dp[j - wv] + vv);
            }
            m -= use;
            k <<= 1;
        }
    }

    cout << dp[W] << '\n';
    return 0;
}
