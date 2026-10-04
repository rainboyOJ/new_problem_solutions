// main.cpp：读入 5×5 矩阵，交换第 m 行和第 n 行后输出。
/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:31
 * update_at: 2026-10-05 02:31
 */

#include <cstdio>

typedef long long ll;

ll a[6][6]; // a[i][j] 表示矩阵第 i 行第 j 列，下标从 1 开始与题面对应
ll m, n;    // 要交换的两个行号（1 ≤ m, n ≤ 5）

int main() {
    // 读入 5×5 矩阵
    for (ll i = 1; i <= 5; ++i)
        for (ll j = 1; j <= 5; ++j)
            scanf("%lld", &a[i][j]);

    scanf("%lld %lld", &m, &n);

    // 交换第 m 行和第 n 行的每一个元素
    for (ll j = 1; j <= 5; ++j) {
        ll t = a[m][j];
        a[m][j] = a[n][j];
        a[n][j] = t;
    }

    // 输出交换后的矩阵，每行元素之间以一个空格分开
    for (ll i = 1; i <= 5; ++i) {
        for (ll j = 1; j <= 5; ++j) {
            if (j > 1)
                printf(" ");
            printf("%lld", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
