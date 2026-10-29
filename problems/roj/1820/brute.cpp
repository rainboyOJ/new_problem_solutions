/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 20:18
 * update_at: 2026-10-29 20:18
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接照题面写：每次询问把区间内所有 i < j 数对枚举一遍，取 A[j] - A[i] 的最大值。
// 单次询问 O(len^2)，q 次询问共 O(n^2 q)，只适合 n <= 300 的小数据。
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 305; // 暴力只处理 n <= 300 的小规模数据

const ll NEG_INF = -2000000000000000000LL;

ll n, q;
ll a[MAXN]; // a[i]：第 i 天的价格，下标从 1 开始

int main() {
    if (scanf("%lld %lld", &n, &q) != 2) return 0;
    if (n > MAXN - 1) { // 超出暴力适用范围，直接退出，避免越界
        fprintf(stderr, "brute.cpp 仅支持 n <= %d\n", MAXN - 1);
        return 0;
    }
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    for (ll t = 0; t < q; t++) {
        ll l, r;
        scanf("%lld %lld", &l, &r);

        ll best = NEG_INF; // 区间内最好的利润，可能为负
        // 枚举区间内所有先买后卖的组合
        for (ll i = l; i <= r; i++) {
            for (ll j = i + 1; j <= r; j++) {
                ll profit = a[j] - a[i];
                if (profit > best) best = profit;
            }
        }
        printf("%lld\n", best);
    }
    return 0;
}
