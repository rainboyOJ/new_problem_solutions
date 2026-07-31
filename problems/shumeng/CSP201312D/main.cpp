/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:44
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const long long MOD = 1000000007LL;

long long dp[MAXN + 1][3][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 首位不能是 0，而合法数的首位只能是 2。
    dp[1][0][1] = 1;

    for (int len = 1; len < MAXN; len++) {
        for (int first = 0; first < 3; first++) {
            for (int second = 0; second < 3; second++) {
                long long ways = dp[len][first][second];
                if (ways == 0) {
                    continue;
                }

                // 状态 first：0 未出现 0，1 已有 0 但没有 1，2 已出现 1。
                if (first < 2) {
                    int next_first = max(first, 1);
                    dp[len + 1][next_first][second] += ways;
                    dp[len + 1][next_first][second] %= MOD;
                }
                if (first > 0) {
                    dp[len + 1][2][second] += ways;
                    dp[len + 1][2][second] %= MOD;
                }

                // 状态 second：0 未出现 2，1 已有 2 但没有 3，2 已出现 3。
                if (second < 2) {
                    int next_second = max(second, 1);
                    dp[len + 1][first][next_second] += ways;
                    dp[len + 1][first][next_second] %= MOD;
                }
                if (second > 0) {
                    dp[len + 1][first][2] += ways;
                    dp[len + 1][first][2] %= MOD;
                }
            }
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << dp[n][2][2] << '\n';
    }

    return 0;
}
