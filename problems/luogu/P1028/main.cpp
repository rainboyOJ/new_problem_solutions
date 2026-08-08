/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n;
int dp[1005];

int main() {
    cin >> n;
    for (int x = 1; x <= n; x++) {
        dp[x] = 1; // 只有 x 本身
        for (int nxt = 1; nxt <= x / 2; nxt++)
            dp[x] += dp[nxt];
    }
    cout << dp[n] << endl;
    return 0;
}
