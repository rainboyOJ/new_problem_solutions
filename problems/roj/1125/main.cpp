/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:03
 * update_at: 2026-10-07 15:03
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 105;

ll a[MAXN][MAXN]; // A 矩阵：n 行 m 列，a[i][j] 是第 i 行第 j 列的元素
ll b[MAXN][MAXN]; // B 矩阵：m 行 k 列，b[t][j] 是第 t 行第 j 列的元素
ll c[MAXN][MAXN]; // C 矩阵：n 行 k 列，c[i][j] 是 A 第 i 行与 B 第 j 列的点积

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lld", &a[i][j]);

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= k; j++)
            scanf("%lld", &b[i][j]);

    // 三重循环按定义算 C：外层枚举行 i 与列 j，内层枚举中间的 t 累加乘积
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++) {
            ll dot = 0; // A 第 i 行与 B 第 j 列的点积，即 C[i][j]
            for (int t = 1; t <= m; t++)
                dot += a[i][t] * b[t][j];
            c[i][j] = dot;
        }

    // 输出 C：每行 k 个整数，整数之间用一个空格分开
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j > 1) printf(" ");
            printf("%lld", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
