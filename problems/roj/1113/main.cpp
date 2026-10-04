/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:16
 * update_at: 2026-10-05 02:16
 */
// main.cpp：不与最大数相同的数字之和。
// 先扫一遍得到最大值，再扫一遍把不等于最大值的数累加。
#include <cstdio>

typedef long long ll;

const int MAXN = 105; // n ≤ 100，留一点余量

ll a[MAXN]; // 序列 a[1..n]

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    ll biggest = 0; // 数列最大值；与它值相等的数全部不参与求和
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        if (i == 1 || a[i] > biggest) biggest = a[i];
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != biggest) ans += a[i];
    }
    printf("%lld\n", ans);
    return 0;
}