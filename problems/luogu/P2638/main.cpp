/**
 * P2638 安全系统
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

unsigned long long C[MAXN * 2][MAXN * 2];

int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    // 组合数 DP：C[i][j] = C[i-1][j] + C[i-1][j-1]
    int max_k = n + max(a, b);
    for (int i = 0; i <= max_k; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    // C(n+a, a) * C(n+b, b)
    unsigned long long ans = C[n + a][a] * C[n + b][b];
    printf("%llu\n", ans);
    return 0;
}
