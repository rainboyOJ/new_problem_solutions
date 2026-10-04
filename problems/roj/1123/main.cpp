/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:45
 * update_at: 2026-10-05 02:46
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 105;   // 图像最大行/列数

ll m, n;                            // 图像的行数、列数
int a[MAXN][MAXN], b[MAXN][MAXN];   // 第一幅、第二幅 01 图像

int main() {
    scanf("%lld %lld", &m, &n);
    // 读入第一幅图像
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    // 读入第二幅图像
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++)
            scanf("%d", &b[i][j]);

    ll same = 0;    // 对应位置像素相同的个数
    for (ll i = 0; i < m; i++)
        for (ll j = 0; j < n; j++)
            if (a[i][j] == b[i][j])
                same++;

    // 相同像素占总像素的百分比，保留两位小数
    printf("%.2f\n", same * 100.0 / (m * n));
    return 0;
}
