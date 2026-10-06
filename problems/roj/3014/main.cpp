/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:51
 * update_at: 2026-10-06 13:51
 */

// 环形均分纸牌：交换相邻摊点等价于把标记搬到相邻格。
// 横向交换只改列计数、纵向交换只改行计数，两个要求完全解耦，
// 各自变成「环形均分纸牌」：代价是前缀和数组到中位数的绝对偏差和。
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 100005;

int n, m, t;
ll row_cnt[MAXN]; // row_cnt[i] = 第 i 行感兴趣的摊点数，之后原地改写成 b 数组
ll col_cnt[MAXN]; // col_cnt[j] = 第 j 列感兴趣的摊点数

// 环形数组的最少相邻交换次数；total 不能被 n 整除时返回 -1 表示不可行。
// 设 f_i 为从位置 i 净搬到位置 i+1 的标记数（下标按环取模），
// 守恒式 f_i = f_(i-1) + a_i - avg 推出 f_i = K + b_i，其中 b_i = S_i - i*avg。
// 代价 sum|f_i| = sum|K + b_i|，K 取 b 的中位数时最小。
// b_n = S_n - n*avg = 0 恒成立，但成环时 K 自由，可取到中位数（区别于线性版）。
ll ring_cost(ll counts[], int len, ll total) {
    if (total % len != 0) return -1;
    ll avg = total / len;
    ll prefix = 0;
    for (int i = 1; i <= len; i++) {
        prefix += counts[i];
        counts[i] = prefix - (ll)i * avg; // 原地改写成 b 数组
    }
    std::sort(counts + 1, counts + len + 1);
    ll pivot = counts[len / 2 + 1]; // 中位数：偶数长度取右中位点，代价相同
    ll sum = 0;
    for (int i = 1; i <= len; i++) sum += counts[i] > pivot ? counts[i] - pivot : pivot - counts[i];
    return sum;
}

int main() {
    scanf("%d %d %d", &n, &m, &t);
    for (int i = 1; i <= t; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        row_cnt[x]++;
        col_cnt[y]++;
    }

    // 行要求和列要求互不干涉，分别判断可行（n|t、m|t）并分别取最小代价
    ll row_cost = ring_cost(row_cnt, n, t);
    ll col_cost = ring_cost(col_cnt, m, t);

    if (row_cost == -1 && col_cost == -1)
        printf("impossible\n");
    else if (col_cost == -1)
        printf("row %lld\n", row_cost);
    else if (row_cost == -1)
        printf("column %lld\n", col_cost);
    else
        printf("both %lld\n", row_cost + col_cost);
    return 0;
}
