/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:45
 * update_at: 2026-10-06 01:45
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 305;

ll a[MAXN];  // 输入序列，下标从 1 开始
ll g[MAXN];  // g[i] = 以 a[i] 开头的最长不下降子序列长度（潜力值：从 i 出发还能延伸多远）
ll ans[MAXN]; // 答案序列（按顺序保存选出的值）
ll n;        // 序列长度

// 阶段 1：倒序 DP 求 g[i] = 1 + max{ g[j] : j > i 且 a[j] >= a[i] }
// 倒着枚举 i，用到的 g[j] 都已算好
void solve_dp() {
    for (ll i = n; i >= 1; --i) {
        g[i] = 1; // 右边接不上任何元素时，a[i] 自己成链
        for (ll j = i + 1; j <= n; ++j)
            if (a[j] >= a[i] && g[j] + 1 > g[i])
                g[i] = g[j] + 1;
    }
}

// 阶段 2：逐位贪心构造字典序最小的最长不下降子序列
// 每一步在 { j > 上一个选中下标 : g[j] >= 还差个数 且 a[j] >= 已选末尾值 }
// 中取 a[j] 最小者；g[j] >= need 用潜力值保证后面一定补得满，
// 值并列时取最靠前的下标，留给后面的选择最多。
void solve_greedy() {
    ll need = 0;    // 还差几个元素才够最长
    for (ll i = 1; i <= n; ++i)
        if (g[i] > need)
            need = g[i]; // need 初值 = 最长长度 L = max g[i]

    ll start = 1;   // 下一个元素只能从 start 及之后取
    ll lower = 0;   // 已选末尾的值；还没选时不设下界（见 lower_used）
    bool lower_used = false;

    ll cnt = 0;     // 已选个数
    while (need > 0) {
        ll best = 0; // 选中的下标，0 表示这一步还没找到候选
        for (ll j = start; j <= n; ++j) {
            if (g[j] < need)          continue;  // 潜力不够，后面凑不满
            if (lower_used && a[j] < lower) continue; // 不满足不下降
            // 比较“值”而不是下标；值并列取最靠前的 j（先遇到的不被覆盖）
            if (best == 0 || a[j] < a[best])
                best = j;
        }
        cnt = cnt + 1;
        ans[cnt] = a[best];
        start = best + 1; // 下标严格递增
        lower = a[best];
        lower_used = true;
        need = need - 1;
    }
    printf("%lld\n", cnt);
    for (ll i = 1; i <= cnt; ++i)
        printf("%lld%c", ans[i], i == cnt ? '\n' : ' ');
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    solve_dp();
    solve_greedy();
    return 0;
}
