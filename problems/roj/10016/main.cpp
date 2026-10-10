/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 07:12
 * update_at: 2026-10-10 08:23
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 2005;          // n <= 2000

ll a[MAXN];                     // a[i]：第 i 个位置的初始值，下标从 1 开始
ll dp[MAXN][MAXN][2];           // dp[i][j][s]：只看前 i 个位置、用了 j 次修改，
                                // s = 0 表示 i 不是山谷点，s = 1 表示 i 是山谷点

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    for (int i = 2; i < n; i++) {       // 首尾都不可能是山谷点
        for (int j = 0; j <= k; j++) {
            if (a[i] < a[i - 1] && a[i] < a[i + 1]) {
                // 原本就是山谷点：不修改就能取值；若它不当山谷点，只能是前一个位置成了山谷点
                dp[i][j][1] = dp[i - 1][j][0] + a[i];
                dp[i][j][0] = dp[i - 1][j][1];
            } else {
                // 原本不是山谷点：花 1 次修改把 a[i] 改成 min(a[i-1]-1, a[i+1]-1)
                if (j > 0) {
                    dp[i][j][1] = dp[i - 1][j - 1][0] + min(a[i - 1] - 1, a[i + 1] - 1);
                }
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1]);
            }
            ans = max(ans, dp[i][j][0]);
            ans = max(ans, dp[i][j][1]);
        }
    }

    cout << ans << "\n";
    return 0;
}
