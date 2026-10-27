/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 14:34
 * update_at: 2026-10-27 14:34
 */
// main2.cpp：P6648 解法二，纯正三角形倍增 + 查询时用 6 块拼出目标三角形。
// 与 main.cpp 的区别：不引入倒三角形，也不做 DAG 递归分解，只保留滚动两层。
// 时间 O(n^2 log k)，空间 O(n^2) 且只有 2 层，与 k 无关。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 3005;

// a[i][j]：第 i 行第 j 列的数。滚动两层，pre 是边长 2^(t-1) 的表，cur 是 2^t 的表。
// 单表最长 3005 x 3005 的 int，约 36 MB，两层合计约 73 MB。
int pre[MAXN][MAXN];
int cur[MAXN][MAXN];

int n, k, lg;

int main() {
    scanf("%d %d", &n, &k);

    // lg = 不超过 k 的最大 2 的幂的指数，即块边长 2^lg <= k。
    lg = 0;
    while ((2 << lg) <= k) {
        lg++;
    }
    int block = 1 << lg;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &pre[i][j]);
        }
    }

    // 倍增：从边长 1 逐层推到边长 block。
    // 边长 2^t 的三角形由 3 个边长 2^(t-1) 的同向三角形拼出，
    // 中间还差一个倒三角，用另外 3 个 2^(t-2) 的块补上（共 6 块）。
    // src / dst 两个指针轮流当读表与写表，避免每层再整表复制一遍。
    int (*src)[MAXN] = pre;
    int (*dst)[MAXN] = cur;
    for (int t = 1; t <= lg; t++) {
        int half = 1 << (t - 1);
        int quarter = 1 << (t - 2);
        for (int i = 1; i + (1 << t) - 1 <= n; i++) {
            for (int j = 1; j <= i; j++) {
                int best = src[i][j];
                if (src[i + half][j] > best) best = src[i + half][j];
                if (src[i + half][j + half] > best) best = src[i + half][j + half];
                if (t > 1) {
                    if (src[i + half][j + quarter] > best) best = src[i + half][j + quarter];
                    if (src[i + quarter][j] > best) best = src[i + quarter][j];
                    if (src[i + quarter][j + quarter] > best) best = src[i + quarter][j + quarter];
                }
                dst[i][j] = best;
            }
        }
        swap(src, dst);
    }

    // 查询：边长 k 的三角形 = 3 个大块 + 3 个边长 2^(lg-1) 的块补空隙。
    // 记 cha = (k - block) / 2，缺的两角各用一个 block 块的上半与下半部分补。
    ll answer = 0;
    for (int i = 1; i + k - 1 <= n; i++) {
        int bottom = i + k - 1;
        for (int j = 1; j <= i; j++) {
            int right = j + k - 1;
            int best = src[i][j];
            if (src[bottom - block + 1][j] > best) best = src[bottom - block + 1][j];
            if (src[bottom - block + 1][right - block + 1] > best) best = src[bottom - block + 1][right - block + 1];
            if (lg >= 1) {
                int cha = (k - block) / 2;
                if (src[bottom - block + 1][j + cha] > best) best = src[bottom - block + 1][j + cha];
                if (src[i + cha][j] > best) best = src[i + cha][j];
                if (src[i + cha][j + cha] > best) best = src[i + cha][j + cha];
            }
            answer += best;
        }
    }

    printf("%lld\n", answer);
    return 0;
}
