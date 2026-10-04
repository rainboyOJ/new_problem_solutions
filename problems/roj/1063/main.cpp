/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:57
 * update_at: 2026-10-04 23:57
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1005;
int a[MAXN]; // a[i] 存放序列的第 i 个数，下标从 1 开始

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);

    // 最小值用第一个真实元素作初值，不能初始化成 0（非负数不代表最小值是 0）
    int mx = a[1], mn = a[1];
    for (int i = 2; i <= n; ++i) {
        if (a[i] > mx) mx = a[i];
        if (a[i] < mn) mn = a[i];
    }
    printf("%d\n", mx - mn); // 最大跨度值 = 最大值 - 最小值
    return 0;
}
