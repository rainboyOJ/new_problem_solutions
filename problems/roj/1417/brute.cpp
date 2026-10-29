/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 19:35
 * update_at: 2026-10-29 20:19
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 按「每个卖出时刻各挑一个买入时刻」的视角写：外层枚举卖出时刻 j，
// 内层把它左边所有 i < j 重新扫一遍，逐个算 R[j] - R[i] 取本行最大。
// 每个 j 都从头重扫左侧，共 O(n^2) 次比较，只适合 n <= 5000 的小数据。
#include <cstdio>

typedef long long ll;

const int MAXN = 5001; // 暴力只处理 n <= 5000 的小规模数据

ll n;
ll r[MAXN]; // r[i]：第 i 个时刻的价格

int main() {
    if (scanf("%lld", &n) != 1) return 0;
    if (n > MAXN - 1) { // 超出暴力适用范围，直接退出，避免越界
        fprintf(stderr, "brute.cpp 仅支持 n <= %d\n", MAXN - 1);
        return 0;
    }
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &r[i]);
    }

    ll ans = -2000000000LL; // 答案可能为负，初值要比 -1e9 更小
    // 外层固定卖出时刻 j，内层把左侧的买入时刻 i 全部重扫一遍
    for (ll j = 1; j < n; j++) {
        for (ll i = 0; i < j; i++) {
            ll profit = r[j] - r[i];
            if (profit > ans) ans = profit;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
