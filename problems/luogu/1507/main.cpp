/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * dp[j][k] 二维01背包
 */
#include <bits/stdc++.h>
using namespace std;

const int maxv = 405;
int H, T, n;
int dp[maxv][maxv];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> H >> T >> n;
    for (int i = 1; i <= n; ++i) {
        int h, t, k;
        cin >> h >> t >> k;
        for (int j = H; j >= h; --j)
            for (int l = T; l >= t; --l)
                dp[j][l] = max(dp[j][l], dp[j - h][l - t] + k);
    }
    cout << dp[H][T] << "\n";
    return 0;
}
