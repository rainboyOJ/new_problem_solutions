/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:16
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接开一张 n*m 的网格，按题意逐格模拟每一次涂色，最后统计每种颜色的格子数。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 105;       // 暴力只服务小数据：网格每维不超过 100
const int MAXC = 2005;      // 颜色数上限

int n, m, k, q;
int grid[MAXN][MAXN];       // grid[i][j] = 0 表示还没被涂色，否则存颜色编号
ll cnt[MAXC];               // cnt[c]：颜色 c 的格子数

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int qi = 1; qi <= q; qi++) {
        int op, l, r, c, t;
        scanf("%d %d %d %d %d", &op, &l, &r, &c, &t);

        if (op == 1) {
            // 涂第 l..r 行的所有格子
            for (int i = l; i <= r; i++) {
                for (int j = 1; j <= m; j++) {
                    // t=1 直接覆盖；t=0 只涂还没被涂过的格子
                    if (t == 1 || grid[i][j] == 0) grid[i][j] = c;
                }
            }
        } else {
            // 涂第 l..r 列的所有格子
            for (int i = 1; i <= n; i++) {
                for (int j = l; j <= r; j++) {
                    if (t == 1 || grid[i][j] == 0) grid[i][j] = c;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] != 0) cnt[grid[i][j]]++;
        }
    }

    for (int c = 1; c <= k; c++) {
        printf("%lld", cnt[c]);
        putchar(c == k ? '\n' : ' ');
    }
    return 0;
}
