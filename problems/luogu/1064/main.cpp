#include <bits/stdc++.h>
using namespace std;

const int MAXN = 32005;

int n, m;
int v[65], p[65], q[65];       // 价格、重要度、主件编号
vector<int> attach[65];         // attach[i] 表示主件 i 的附件列表
// dp[j] 表示花费 j 元能获得的最大价值（价格 × 重要度）。
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> v[i] >> p[i] >> q[i];
        if (q[i] != 0) {
            attach[q[i]].push_back(i); // 附件挂到对应主件下
        }
    }

    for (int i = 1; i <= m; i++) {
        if (q[i] != 0) continue;      // 只处理主件

        int sz = attach[i].size();
        // 枚举当前主件的所有附件组合（2^sz 种）
        for (int j = n; j >= 0; j--) {
            for (int mask = 0; mask < (1 << sz); mask++) {
                int cost = v[i];
                int val = v[i] * p[i];  // 主件必选
                bool ok = true;
                for (int k = 0; k < sz; k++) {
                    if (mask >> k & 1) {
                        int a = attach[i][k];
                        cost += v[a];
                        val += v[a] * p[a];
                    }
                }
                if (j >= cost) {
                    dp[j] = max(dp[j], dp[j - cost] + val);
                }
            }
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
