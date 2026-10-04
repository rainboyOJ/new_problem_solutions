/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:43
 * update_at: 2026-10-04 23:43
 */
#include <cstdio>

typedef long long ll;

ll x, y;

int main() {
    scanf("%lld %lld", &x, &y);
    // 点在以原点为中心、边与坐标轴平行的单位正方形内或边界上
    // 当且仅当 x 和 y 都落在闭区间 [-1, 1] 内
    if (x >= -1 && x <= 1 && y >= -1 && y <= 1)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}
