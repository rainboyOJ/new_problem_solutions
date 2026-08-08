#include <bits/stdc++.h>
using namespace std;

const int MAXT = 1005;

int T, n;
// dp[j] 表示在 j 分钟内能获得的最大美学值。
int dp[MAXT];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h1, m1, h2, m2;
    char colon;
    cin >> h1 >> colon >> m1;
    cin >> h2 >> colon >> m2;
    cin >> n;

    T = (h2 * 60 + m2) - (h1 * 60 + m1);  // 总可用分钟数

    for (int i = 1; i <= n; i++) {
        int t, c, p;
        cin >> t >> c >> p;               // 花费时间 t，美学值 c，次数 p

        if (p == 0) {                      // 能看无限次 → 完全背包正序
            for (int j = t; j <= T; j++) {
                dp[j] = max(dp[j], dp[j - t] + c);
            }
        } else {                           // 有限次 → 二进制分组转为 0/1 背包倒序
            int k = 1;
            while (p > 0) {
                int use = min(k, p);
                int wt = use * t;
                int wc = use * c;
                for (int j = T; j >= wt; j--) {
                    dp[j] = max(dp[j], dp[j - wt] + wc);
                }
                p -= use;
                k <<= 1;
            }
        }
    }

    cout << dp[T] << '\n';
    return 0;
}
