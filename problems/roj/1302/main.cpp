/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:33
 * update_at: 2026-10-05 08:33
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 100005;

int n;                                 // 当前这一组数据的天数 N
int p[MAXN];                           // p[i]：第 i 天（1-indexed）的价格
int suf[MAXN];                         // suf[i]：第 i..N 天内只做一次买卖的最大利润（同天买卖记 0）

// 在价格序列 p[1..n] 上求两笔交易（第一笔卖出日 ≤ 第二天买入日）能拿到的最大总利润。
ll max_two_trades() {
    memset(suf, 0, sizeof(suf));

    // 反向扫描：suf[i] = 仅在第 i..n 天做一次买卖的最大利润
    int high = p[n];                 // 第 i 天右侧见过的最高卖出价
    int best = 0;                    // 第 i..n 天窗口里一次买卖的最大利润，天然不小于 0
    for (int i = n - 1; i >= 1; --i) {
        best = (best > high - p[i]) ? best : (high - p[i]); // 第 i 天买入、右侧最高价卖出
        suf[i] = best;
        high = (high > p[i]) ? high : p[i];
    }

    // 正向扫描：枚举拆分点 i，把两笔交易拆成 [1..i] 与 [i..n] 两个独立子问题
    ll ans = 0;
    int low = p[1];                  // 前缀里见过的最低买入价
    int gain = 0;                    // 前缀 [1..i] 内做一次买卖的最大利润，也天然不小于 0
    for (int i = 1; i <= n; ++i) {
        low = (low < p[i]) ? low : p[i];
        gain = (gain > p[i] - low) ? gain : (p[i] - low);
        ll cur = (ll)gain + suf[i]; // 第一笔整体落在 [0..i]，第二笔落在 [i..n]
        if (cur > ans) ans = cur;
    }
    return ans;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &p[i]);
        printf("%lld\n", max_two_trades());
    }
    return 0;
}