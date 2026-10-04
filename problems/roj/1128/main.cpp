/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:52
 * update_at: 2026-10-05 02:52
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 105;

int n, m;
int src[MAXN][MAXN]; // src[r][c] = 原图像灰度值，模糊结果只从这里读
int res[MAXN][MAXN]; // res[r][c] = 模糊后的灰度值

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &src[i][j]);

    // 最外侧一圈像素不变：直接把原图复制成结果，再只改内部
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            res[i][j] = src[i][j];

    // 只处理内部像素（第 2~n-1 行、第 2~m-1 列），
    // 循环范围天然跳过边界，也保证 i±1、j±1 不会越界
    for (int i = 2; i <= n - 1; i++)
        for (int j = 2; j <= m - 1; j++) {
            // 十字 5 格之和：自身 + 上下左右（全部取原灰度值）
            int s = src[i][j] + src[i - 1][j] + src[i + 1][j] + src[i][j - 1] + src[i][j + 1];
            // s 是整数，s/5 的小数部分只可能是 .0/.2/.4/.6/.8，不会出现 .5 平局，
            // 所以 (2*s+5)/10 就是四舍五入到最接近的整数，不需要浮点
            res[i][j] = (2 * s + 5) / 10;
        }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d", res[i][j]);
            if (j < m)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
