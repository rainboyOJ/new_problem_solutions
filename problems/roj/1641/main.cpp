/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:29
 * update_at: 2026-10-06 01:29
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 105;

ll a[MAXN][MAXN]; // 矩阵 A，n 行 m 列
ll b[MAXN][MAXN]; // 矩阵 B，m 行 p 列
ll c[MAXN][MAXN]; // 结果矩阵 C，n 行 p 列

int main() {
    int n, m, p;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    scanf("%d", &p);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= p; j++) {
            scanf("%lld", &b[i][j]);
        }
    }

    // 按定义计算 C[i][j] = sum_{k=1}^{m} A[i][k] * B[k][j]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= p; j++) {
            ll sum = 0;
            for (int k = 1; k <= m; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= p; j++) {
            printf("%lld", c[i][j]);
            if (j < p) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
