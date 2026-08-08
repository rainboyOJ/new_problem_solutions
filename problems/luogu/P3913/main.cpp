/**
 * P3913 车的攻击
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int rows[MAXN], cols[MAXN];
int n, k;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i) {
        scanf("%d%d", &rows[i], &cols[i]);
    }
    sort(rows + 1, rows + k + 1);
    sort(cols + 1, cols + k + 1);
    // 去重后统计不同行数和列数
    int row_cnt = unique(rows + 1, rows + k + 1) - (rows + 1);
    int col_cnt = unique(cols + 1, cols + k + 1) - (cols + 1);
    // 被攻击格子数 = 行 * n + 列 * n - 行 * 列
    long long ans = 1LL * row_cnt * n + 1LL * col_cnt * n - 1LL * row_cnt * col_cnt;
    printf("%lld\n", ans);
    return 0;
}
