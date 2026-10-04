/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:40
 * update_at: 2026-10-05 02:40
 */
#include <cstdio>

typedef long long ll; // 题目数据统一用 long long

const int MAXN = 105;
const int MAXM = 105;

ll a[MAXN][MAXM]; // a[i][j] 表示原图第 i 行第 j 列的像素（下标从 1 开始）

// 题意：把 n 行 m 列的图像顺时针旋转 90 度后输出，结果为 m 行 n 列
// 旋转后 b[i][j] = a[n-j+1][i]，即新图第 i 行等于原图第 i 列从下往上读
int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0;

    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= m; ++j) {
            scanf("%lld", &a[i][j]);
        }
    }

    for (ll i = 1; i <= m; ++i) {
        for (ll j = n; j >= 1; --j) {
            if (j != n) printf(" ");
            printf("%lld", a[j][i]); // 原图第 i 列自下而上
        }
        printf("\n");
    }
    return 0;
}
