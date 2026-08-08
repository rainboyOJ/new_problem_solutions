/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:59
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 105;
const int MAXV = 105;
const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int n, V;
int v[MAXN], w[MAXN];
int dp[MAXV];   // dp[c] 表示恰好装满容量 c 时的最大价值，-INF 表示不可达
int cnt[MAXV];  // cnt[c] 表示达到 dp[c] 的方案数

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> V;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    // 恰好装满初始化：只有 dp[0] 可达
    for (int c = 1; c <= V; ++c) dp[c] = -INF;
    cnt[0] = 1;

    // 01 背包 DP + 方案计数（恰好装满）
    for (int i = 1; i <= n; ++i) {
        for (int c = V; c >= v[i]; --c) {
            if (dp[c - v[i]] == -INF) continue; // 前驱不可达则跳过
            int val = dp[c - v[i]] + w[i];
            if (val > dp[c]) {
                dp[c] = val;
                cnt[c] = cnt[c - v[i]];
            } else if (val == dp[c]) {
                cnt[c] = (cnt[c] + cnt[c - v[i]]) % MOD;
            }
        }
    }

    if (dp[V] == -INF) cout << 0 << '\n';
    else cout << cnt[V] % MOD << '\n';
    return 0;
}
