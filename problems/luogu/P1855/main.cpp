/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 二维费用01背包，价值为1（愿望数）
 */
#include <bits/stdc++.h>
using namespace std;

const int maxv = 205;
int n, M, T;
int dp[maxv][maxv];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> M >> T;
    for (int i = 1; i <= n; ++i) {
        int m, t;
        cin >> m >> t;
        for (int j = M; j >= m; --j)
            for (int k = T; k >= t; --k)
                dp[j][k] = max(dp[j][k], dp[j - m][k - t] + 1);
    }
    cout << dp[M][T] << "\n";
    return 0;
}
