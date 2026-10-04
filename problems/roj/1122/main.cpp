/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:31
 * update_at: 2026-10-05 02:31
 */
#include <cstdio>

typedef long long ll; // 题目数据统一用 long long

const int N = 5; // 矩阵固定 5 行 5 列

ll a[N + 1][N + 1];    // a[i][j] 表示第 i 行第 j 列的元素，行列均从 1 编号
ll col_min[N + 1];     // col_min[j] 表示第 j 列的最小值（题目保证每列唯一）

int main() {
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            scanf("%lld", &a[i][j]);

    // 预处理每列最小值，之后验证"列最小"只需一次比较
    for (int j = 1; j <= N; ++j) {
        col_min[j] = a[1][j];
        for (int i = 2; i <= N; ++i)
            if (a[i][j] < col_min[j]) col_min[j] = a[i][j];
    }

    // 鞍点必然是该行最大值；每行最大值唯一，逐行取一个候选再验证列最小性
    for (int i = 1; i <= N; ++i) {
        int max_col = 1; // 本行最大值的列号
        for (int j = 2; j <= N; ++j)
            if (a[i][j] > a[i][max_col]) max_col = j;
        if (a[i][max_col] == col_min[max_col]) {
            printf("%d %d %lld\n", i, max_col, a[i][max_col]);
            return 0;
        }
    }

    printf("not found\n");
    return 0;
}
