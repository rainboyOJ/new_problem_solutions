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

int n, V;
int v[MAXN], w[MAXN];
int dp[MAXV];   // dp[c] 表示容量不超过 c 时的最大价值
int cnt[MAXV];  // cnt[c] 表示达到 dp[c] 的方案数

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> V;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    // 初始化：空集是每一种容量下价值为 0 的唯一方案
    for (int c = 0; c <= V; ++c) cnt[c] = 1;

    // 01 背包 DP + 方案计数
    for (int i = 1; i <= n; ++i) {
        for (int c = V; c >= v[i]; --c) {
            int val = dp[c - v[i]] + w[i];
            if (val > dp[c]) {
                dp[c] = val;
                cnt[c] = cnt[c - v[i]];
            } else if (val == dp[c]) {
                cnt[c] = (cnt[c] + cnt[c - v[i]]) % MOD;
            }
        }
    }

    cout << cnt[V] % MOD << '\n';
    return 0;
}
