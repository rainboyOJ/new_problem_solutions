/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:20
 * update_at: 2026-10-05 07:20
 */

#include <cstdio>

typedef long long ll;

const int MAXR = 1005;

int r;                 // 金字塔的行数
ll a[MAXR][MAXR];      // a[i][j] 表示第 i 行第 j 列的数字
ll best[MAXR];         // best[c] 表示"从当前行第 c 列出发走到底部"的最大路径和

// 自底向上逐层递推：f(i,c) = a[i][c] + max(f(i+1,c), f(i+1,c+1))
// 用一维数组滚动，空间 O(R)
void solve() {
    // 初始时 best 就是最后一行自己：最后一行的点走到底部就是停在原地
    for (int c = 1; c <= r; ++c)
        best[c] = a[r][c];

    // 从倒数第二行往上，每层用下一层的 best 更新
    // 第 c 列的两个后继是下一层的 c 列和 c+1 列，取较大的那个转移
    for (int i = r - 1; i >= 1; --i)
        for (int c = 1; c <= i; ++c)
            best[c] = a[i][c] + (best[c] > best[c + 1] ? best[c] : best[c + 1]);

    printf("%lld\n", best[1]);
}

int main() {
    scanf("%d", &r);
    for (int i = 1; i <= r; ++i)
        for (int c = 1; c <= i; ++c)
            scanf("%lld", &a[i][c]);
    solve();
    return 0;
}
