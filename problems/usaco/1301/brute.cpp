/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:48
 * update_at: 2026-07-11 16:49
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const long long INF = (1LL << 60);

int n;
long long k;
long long day_arr[MAXN];
long long dp[MAXN]; // dp[i] 表示覆盖前 i 个观看日的最小费用

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> day_arr[i];
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    // 小数据暴力 DP：枚举最后一个订阅段覆盖哪些观看日。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            long long len = day_arr[i] - day_arr[j] + 1;
            dp[i] = min(dp[i], dp[j - 1] + len + k);
        }
    }

    cout << dp[n] << '\n';

    return 0;
}
