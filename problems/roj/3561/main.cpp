/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:05
 * update_at: 2026-10-06 14:05
 */

#include <bits/stdc++.h>
typedef long long ll;

const int MAXN = 1005;

ll m, n, k, l, d;
int row_cnt[MAXN]; // row_cnt[i] = 第 i 行与 i+1 行之间开通道能隔开的说话对数
int col_cnt[MAXN]; // col_cnt[j] = 第 j 列与 j+1 列之间开通道能隔开的说话对数
int row_id[MAXN];  // 行缝编号，用于排序
int col_id[MAXN];  // 列缝编号，用于排序

// 比较函数：按隔开的对数从大到小排序
bool cmp_row(int a, int b) {
    return row_cnt[a] > row_cnt[b];
}
bool cmp_col(int a, int b) {
    return col_cnt[a] > col_cnt[b];
}

int main() {
    scanf("%lld %lld %lld %lld %lld", &m, &n, &k, &l, &d);
    for (int i = 1; i < m; i++) row_id[i] = i; // 行缝编号 1..m-1
    for (int j = 1; j < n; j++) col_id[j] = j; // 列缝编号 1..n-1

    // 每对说话同学：前后相邻给行缝计数，左右相邻给列缝计数，跨缝编号取较小坐标
    for (int i = 1; i <= d; i++) {
        ll x, y, p, q;
        scanf("%lld %lld %lld %lld", &x, &y, &p, &q);
        if (x == p)
            col_cnt[y < q ? y : q]++; // 左右相邻，隔开它的是列缝 min(y,q)
        else
            row_cnt[x < p ? x : p]++; // 前后相邻，隔开它的是行缝 min(x,p)
    }

    // 各取隔开对数最多的 K / L 条缝：按贡献排序取前 K（L）个下标
    std::sort(row_id + 1, row_id + m, cmp_row);
    std::sort(col_id + 1, col_id + n, cmp_col);

    // 选中的缝编号升序输出
    std::sort(row_id + 1, row_id + k + 1);
    std::sort(col_id + 1, col_id + l + 1);
    for (int i = 1; i <= k; i++) printf("%d%c", row_id[i], i == k ? '\n' : ' ');
    for (int j = 1; j <= l; j++) printf("%d%c", col_id[j], j == l ? '\n' : ' ');
    return 0;
}
