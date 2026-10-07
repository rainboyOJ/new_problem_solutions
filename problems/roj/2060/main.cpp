/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:36
 * update_at: 2026-10-06 10:36
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n, T, M;               // 歌曲数、CD 容量、CD 张数
ll a[25];                 // 每首歌的长度
ll dp[25][25];            // dp[d][u]：已开 d 张 CD、最后一张已用 u 分钟时最多可选歌曲数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T >> M;
    for (ll i = 1; i <= n; ++i) cin >> a[i];

    // 初始化：只有 (0,0) 可达，其余为负无穷
    for (ll d = 0; d <= M; ++d)
        for (ll u = 0; u <= T; ++u)
            dp[d][u] = -1e9;
    dp[0][0] = 0;

    for (ll k = 1; k <= n; ++k) {           // 按创作顺序处理每首歌
        ll old[25][25];
        for (ll d = 0; d <= M; ++d)
            for (ll u = 0; u <= T; ++u)
                old[d][u] = dp[d][u];

        for (ll d = 0; d <= M; ++d) {
            for (ll u = 0; u <= T; ++u) {
                if (old[d][u] < 0) continue; // 不可达状态跳过

                // 1) 丢弃这首歌
                dp[d][u] = max(dp[d][u], old[d][u]);

                // 2) 接在当前 CD 末尾（前提是已经开过 CD）
                if (d >= 1 && u + a[k] <= T) {
                    dp[d][u + a[k]] = max(dp[d][u + a[k]], old[d][u] + 1);
                }

                // 3) 另开一张新 CD
                if (d < M && a[k] <= T) {
                    dp[d + 1][a[k]] = max(dp[d + 1][a[k]], old[d][u] + 1);
                }
            }
        }
    }

    ll ans = 0;
    for (ll d = 0; d <= M; ++d)
        for (ll u = 0; u <= T; ++u)
            ans = max(ans, dp[d][u]);

    cout << ans << "\n";
    return 0;
}
