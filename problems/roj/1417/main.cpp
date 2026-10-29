/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 19:35
 * update_at: 2026-10-29 19:35
 */
// main.cpp：ROJ 1417 最大利润（AOJ ALDS1_1_D）。
// 从左往右扫一遍，维护「扫到当前位置之前出现过的最低价格」min_price。
// 对每个卖出时刻 j，它能拿到的最大利润就是 R[j] - min_price，用它更新答案。
// 价格只被用一次，不必落地成数组：读到就更新 min_price，额外空间 O(1)。
#include <cstdio>

typedef long long ll;

const ll NEG_INF = -2000000000LL; // 答案可能为负（价格一路下跌），初值要比 -1e9 更小

ll n;
ll min_price; // min(R[0..j-1])：扫到当前时刻之前出现过的最低价格
ll ans;       // 目前见过的最好利润

void solve() {
    if (scanf("%lld", &n) != 1) return; // 单组输入：第一行 n

    ll price;
    scanf("%lld", &price);
    min_price = price; // 第 0 个时刻只能当买入点，先把它记为最低价
    ans = NEG_INF;

    for (ll j = 1; j < n; j++) {
        scanf("%lld", &price);
        // 先算利润、再更新最低价，保证买入时刻严格早于卖出时刻
        ll profit = price - min_price;
        if (profit > ans) ans = profit;
        if (price < min_price) min_price = price;
    }

    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
