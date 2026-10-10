/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 花店橱窗布置：后缀 DP + 贪心还原字典序最小方案
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXF = 512;
const int MAXV = 512;
const ll NEG = -(1LL << 50); // 不可行状态哨兵

ll a[MAXF][MAXV]; // a[i][j]：第 i 朵花放进第 j 个花瓶的美观度（均 1 起编号）
// g[i][j]：第 i..F 朵花放进花瓶 j..V 的最大美观度（后缀 DP）
ll g[MAXF][MAXV];
ll pos[MAXF]; // 还原出来的方案：第 i 朵花的花瓶编号

int main() {
    int f, v;
    if (scanf("%d %d", &f, &v) != 2) {
        return 0;
    }
    for (int i = 1; i <= f; i++) {
        for (int j = 1; j <= v; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for (int i = 1; i <= f + 1; i++) {
        for (int j = 0; j <= v + 2; j++) {
            g[i][j] = NEG;
        }
    }
    for (int j = 0; j <= v + 2; j++) {
        g[f + 1][j] = 0; // 没有花要放：任何花瓶区间都是 0
    }

    for (int i = f; i >= 1; i--) {
        // 第 i 朵花放 j 时前面还剩 i-1 朵花，所以 j 至少是 v-f+i
        for (int j = v - f + i; j >= 1; j--) {
            g[i][j] = max(a[i][j] + g[i + 1][j + 1], g[i][j + 1]);
        }
    }

    // 贪心还原字典序最小方案：第 i 朵花取最小的花瓶 j，使得「放 j + 后缀最优」仍等于整体最优
    int j = 1;
    for (int i = 1; i <= f; i++) {
        while (j <= v && a[i][j] + g[i + 1][j + 1] != g[i][j]) {
            j++;
        }
        pos[i] = j;
        j++;
    }

    printf("%lld\n", g[1][1]);
    for (int i = 1; i <= f; i++) {
        if (i > 1) printf(" ");
        printf("%lld", pos[i]);
    }
    printf("\n");
    return 0;
}
