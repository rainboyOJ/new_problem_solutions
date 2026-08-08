/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 完全背包求最小值，dp[0]=0, dp[c]=min(dp[c], dp[c-w]+1)
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005, INF = 1e9;
int m;
int dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> m;
    fill(dp, dp + m + 1, INF);
    dp[0] = 0;
    for (int i = 1; ; ++i) {
        int w = i * i * i * i;
        if (w > m) break;
        for (int j = w; j <= m; ++j)
            dp[j] = min(dp[j], dp[j - w] + 1);
    }
    cout << dp[m] << "\n";
    return 0;
}
