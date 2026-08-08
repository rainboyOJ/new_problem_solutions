/**
 * P3156 【深基15.例1】询问学号
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 5;

// 学号数组，按入场顺序存放，下标从 1 开始
int a[MAXN];
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    // 读入 n 个学号
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    // 处理 m 次询问，题目编号从 1 开始，直接输出 a[query]
    while (m--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", a[x]);
    }
    return 0;
}
