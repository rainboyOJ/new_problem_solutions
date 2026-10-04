// main.cpp：O(FV) 线性 DP 求最大美学值，再逐层回溯输出方案。
/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:51
 * update_at: 2026-10-05 07:51
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 105;
const ll NEG = -1e9; // 表示“用前 t 个花瓶放不下 i 束花”

int f, v;
int a[MAXN][MAXN]; // a[i][j]：花束 i 放进花瓶 j 的美学值
ll g[MAXN][MAXN];  // g[i][t]：花束 1..i 依次放进编号不超过 t 的花瓶的最大美学值
int pick[MAXN];    // pick[i]：第 i 束花选的花瓶编号

// 填前缀最大值表：花瓶 t 要么空着（g[i][t-1]），要么插第 i 束花（g[i-1][t-1]+a[i][t]）
void solve() {
    for (int t = 0; t <= v; ++t)
        g[0][t] = 0; // 没有花束时美学值为 0
    for (int i = 1; i <= f; ++i) {
        g[i][i - 1] = NEG; // 不足 i 个花瓶放不下 i 束花
        for (int t = i; t <= v; ++t) {
            ll best = g[i][t - 1]; // 花瓶 t 空着
            if (g[i - 1][t - 1] + a[i][t] > best)
                best = g[i - 1][t - 1] + a[i][t]; // 花瓶 t 插第 i 束花
            g[i][t] = best;
        }
    }

    // 从右往左回溯：g[i] 逐层单调不减，取最靠左、又取到该层目标值的花瓶，
    // 这个位置一定来自“插花”那一支，编号天然严格递增；
    // t < i 时 g[i][t] = NEG，不会误配，循环必然停在 [i, v] 内
    ll target = g[f][v];
    for (int i = f; i >= 1; --i) {
        int pos = i; // 第一个取到 target 的位置，必有 g[i][pos] == target
        while (g[i][pos] < target)
            ++pos;
        pick[i] = pos;
        target = g[i - 1][pos - 1]; // 前 i-1 束花的目标值
    }

    printf("%lld\n", g[f][v]);
    for (int i = 1; i <= f; ++i)
        printf("%d%c", pick[i], i == f ? '\n' : ' ');
}

int main() {
    scanf("%d %d", &f, &v);
    for (int i = 1; i <= f; ++i)
        for (int j = 1; j <= v; ++j)
            scanf("%d", &a[i][j]);
    solve();
    return 0;
}
