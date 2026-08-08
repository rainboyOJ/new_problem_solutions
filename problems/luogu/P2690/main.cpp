#include <bits/stdc++.h>
using namespace std;

const int MAXT = 1005;
const int MAXW = 35;
const int NEG_INF = -0x3f3f3f3f;

int t, w;
int a[MAXT];
int dp[MAXT][MAXW];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t >> w;
    for (int i = 1; i <= t; i++) {
        cin >> a[i];
    }

    for (int i = 0; i <= t; i++) {
        for (int j = 0; j <= w; j++) {
            dp[i][j] = NEG_INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= t; i++) {
        for (int j = 0; j <= w; j++) {
            // 不在这一分钟前移动。
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);

            // 在这一分钟前从另一棵树移动过来。
            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
            }

            // 移动次数的奇偶决定当前位置：
            // 偶数次在 1 号树下，奇数次在 2 号树下。
            int pos = (j % 2 == 0 ? 1 : 2);
            if (pos == a[i]) {
                dp[i][j]++;
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= w; j++) {
        ans = max(ans, dp[t][j]);
    }

    cout << ans << '\n';
    return 0;
}
