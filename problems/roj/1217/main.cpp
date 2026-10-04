/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:50
 * update_at: 2026-10-05 05:50
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 8;      // n <= 8

int n, k;                // 棋盘边长与要摆的棋子数
ll ans;                  // 当前棋盘的方案数
ll rowMask[MAXN];        // rowMask[r]：第 r 行的 '#' 压成的 n 位掩码，第 c 位为 1 表示 (r,c) 可放

// 记忆化：memo[row][used] 表示第 row 行及以下、列占用掩码为 used 时的方案数
// -1 表示还没算过；每行至多一枚棋子，已放枚数就是 used 里 1 的个数
ll memo[MAXN + 1][1 << MAXN];
bool vis[MAXN + 1][1 << MAXN]; // 对应状态是否已算过

// 第 row 行及以下、列占用为 used 时，把剩余棋子放完的方案数
// 还差枚数 = k - used 中 1 的个数
ll dfs(int row, int used) {
    int rest = k - __builtin_popcount(used);
    if (rest == 0) return 1;                 // 棋子恰好放完：记 1 种方案
    if (n - row < rest) return 0;            // 剩余行数不够摆：剪枝
    if (vis[row][used]) return memo[row][used];

    ll res = dfs(row + 1, used);             // 本行不放棋子
    int freeMask = rowMask[row] & ~used;     // 本行可放且列还空闲的格子
    for (int c = 0; c < n; c++) {
        if (freeMask >> c & 1) {
            // 本行在第 c 列放一枚棋子
            res += dfs(row + 1, used | (1 << c));
        }
    }
    vis[row][used] = true;
    memo[row][used] = res;
    return res;
}

int main() {
    while (true) {
        scanf("%d %d", &n, &k);
        if (n == -1 && k == -1) break;       // 题面的输入结束标记

        for (int r = 0; r < n; r++) {
            char s[MAXN + 2];
            scanf("%s", s);
            rowMask[r] = 0;
            for (int c = 0; c < n; c++) {
                if (s[c] == '#') rowMask[r] |= 1LL << c;
            }
        }

        // 清空记忆化：不同棋盘不能共用状态
        for (int r = 0; r <= n; r++) {
            for (int m = 0; m < (1 << n); m++) vis[r][m] = false;
        }
        ans = dfs(0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
