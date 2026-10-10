/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 乌龟棋：状态只记四类卡片各用了几张
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 400;

ll board[MAXN];        // board[i]：第 i+1 个格子的分数
ll cnt[5];             // cnt[k]：写着数字 k 的卡片张数
// dp[c1 维奇偶][c2][c3][c4]：四类卡各用了这么多张时能得到的最大得分
ll dp[2][42][42][42];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &board[i]);
    }
    for (int i = 0; i < m; i++) {
        int b;
        scanf("%d", &b);
        cnt[b]++;
    }

    int n1 = cnt[1], n2 = cnt[2], n3 = cnt[3], n4 = cnt[4];
    const ll NEG = -(1LL << 50); // 不可达状态哨兵，远低于任何真实得分

    for (int c1 = 0; c1 <= n1; c1++) {
        int cur = c1 & 1, pre = (c1 - 1) & 1; // c1 维滚动，只留上一层平面
        for (int c2 = 0; c2 <= n2; c2++) {
            for (int c3 = 0; c3 <= n3; c3++) {
                for (int c4 = 0; c4 <= n4; c4++) {
                    int pos = c1 + 2 * c2 + 3 * c3 + 4 * c4; // 四元组唯一确定落点
                    if (pos == 0) {
                        dp[cur][0][0][0] = board[0]; // 起点：自动获得第 1 格的分数
                        continue;
                    }
                    ll best = NEG;
                    if (c1 > 0) best = max(best, dp[pre][c2][c3][c4]);      // 最后一手用 1 卡
                    if (c2 > 0) best = max(best, dp[cur][c2 - 1][c3][c4]);  // 最后一手用 2 卡
                    if (c3 > 0) best = max(best, dp[cur][c2][c3 - 1][c4]);  // 最后一手用 3 卡
                    if (c4 > 0) best = max(best, dp[cur][c2][c3][c4 - 1]);  // 最后一手用 4 卡
                    dp[cur][c2][c3][c4] = best + board[pos]; // 四类前驱同处一格，格子分是公共加项
                }
            }
        }
    }

    printf("%lld\n", dp[n1 & 1][n2][n3][n4]); // 用光全部卡片，落点必是第 n 格
    return 0;
}
