/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:09
 * update_at: 2026-10-05 08:09
 */

// 数字三角形：自底向上 DP，dp[j] 表示从当前行第 j 列出发到底部的最大路径和。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXH = 105; // h <= 100

int h;             // 三角形高度
ll tri[MAXH][MAXH]; // tri[r][j] 表示第 r 行第 j 列的数字（下标从 1 开始）
ll dp[MAXH];        // 滚动数组：dp[j] = 从当前行第 j 列出发到底部的最大路径和

int main() {
    scanf("%d", &h);
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= i; j++)
            scanf("%lld", &tri[i][j]);

    // 初始化为最底层一行：从底层出发的最大和就是自身
    for (int j = 1; j <= h; j++) dp[j] = tri[h][j];

    // 自底向上递推：f(r,j) = a(r,j) + max(f(r+1,j), f(r+1,j+1))
    for (int i = h - 1; i >= 1; i--)
        for (int j = 1; j <= i; j++)
            dp[j] = tri[i][j] + max(dp[j], dp[j + 1]);

    printf("%lld\n", dp[1]);
    return 0;
}
