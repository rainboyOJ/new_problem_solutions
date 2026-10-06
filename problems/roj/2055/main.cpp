/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:28
 * update_at: 2026-10-06 10:28
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 255;
int n;                       // 牧场边长
char grid[MAXN][MAXN];       // 输入网格，'1' 表示完好，'0' 表示毁坏
int f[MAXN][MAXN];           // f[r][c] = 以 (r,c) 为右下角的最大全 1 正方形边长
int sizes[MAXN];             // sizes[k] = 恰好以边长 k 结尾的格子个数
int cnt[MAXN];               // cnt[k] = 边长为 k 的全 1 正方形总数

int main() {
    scanf("%d", &n);
    for (int r = 1; r <= n; r++) {
        scanf("%s", grid[r] + 1);
    }

    // 逐格递推最大全 1 正方形：min(上、左、左上) + 1
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (grid[r][c] != '1') {
                continue;
            }
            int up = f[r - 1][c];
            int left = f[r][c - 1];
            int up_left = f[r - 1][c - 1];
            int best = up < left ? up : left;
            if (up_left < best) {
                best = up_left;
            }
            f[r][c] = best + 1;
            sizes[f[r][c]]++;
        }
    }

    // 边长为 k 的正方形总数 = 所有 f >= k 的格子数，从大到小做后缀和
    int total = 0;
    for (int k = n; k >= 2; k--) {
        total += sizes[k];
        cnt[k] = total;
    }

    // 只输出确实存在的尺寸
    for (int k = 2; k <= n; k++) {
        if (cnt[k] > 0) {
            printf("%d %d\n", k, cnt[k]);
        }
    }
    return 0;
}
