/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:27
 * update_at: 2026-11-11 00:27
 */
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 360;
const int MAXC = 42;

int a[MAXN];
int cnt[5];
int dp[MAXC][MAXC][MAXC][MAXC];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < m; ++i) {
        int card;
        cin >> card;
        cnt[card]++;
    }

    // 初始状态：一张卡都不用，位于第 1 格
    dp[0][0][0][0] = a[1];

    for (int c1 = 0; c1 <= cnt[1]; ++c1) {
        for (int c2 = 0; c2 <= cnt[2]; ++c2) {
            for (int c3 = 0; c3 <= cnt[3]; ++c3) {
                for (int c4 = 0; c4 <= cnt[4]; ++c4) {
                    if (c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0) continue;

                    // 根据各类卡片张数计算当前乌龟所在格子位置
                    int pos = 1 + c1 * 1 + c2 * 2 + c3 * 3 + c4 * 4;
                    int max_prev = 0;

                    if (c1 > 0) max_prev = max(max_prev, dp[c1 - 1][c2][c3][c4]);
                    if (c2 > 0) max_prev = max(max_prev, dp[c1][c2 - 1][c3][c4]);
                    if (c3 > 0) max_prev = max(max_prev, dp[c1][c2][c3 - 1][c4]);
                    if (c4 > 0) max_prev = max(max_prev, dp[c1][c2][c3][c4 - 1]);

                    dp[c1][c2][c3][c4] = max_prev + a[pos];
                }
            }
        }
    }

    cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]] << "\n";

    return 0;
}
