/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:15
 * update_at: 2026-10-05 12:15
 *
 * 股票交易（SCOI 2010 / 一本通 5.5 练习 4）
 * DP：f[i][j] = 第 i 天结束时持有 j 股的最大现金。
 * 第 i 天交易的前驱固定为第 p = max(i-W-1, 0) 天结束时的状态（间隔 W 天）。
 * 买入/卖出转移各是一个随 j 平移的固定长度窗口最值，拆项后用单调队列摊还 O(1)，
 * 总复杂度 O(T * MaxP)。
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 2005;
const ll NEG = -1000000000000000000LL; // 不可达哨兵：真实钱数下界约 -8e9，远离此值

int T, MaxP, W;
ll AP[MAXN], BP[MAXN]; // 第 i 天的买入价 / 卖出价
ll AS[MAXN], BS[MAXN]; // 第 i 天一次买入 / 卖出的股数上限
ll f[MAXN][MAXN];      // f[i][j]：第 i 天结束时持有 j 股的最大现金
int que[MAXN];         // 单调队列，存持股数下标
int qh, qt;            // 队头 / 队尾（半开区间 [qh, qt)）

// 买入转移：对每个 j，从窗口 j' ∈ [j-AS, j-1] 里取 f[p][j'] - AP*(j-j') 的最大值写进 f[i][j]
// 窗口里被比较的量 g(j') = f[p][j'] + AP*j' 与 j 无关，j 增大时窗口整体右移一格
void transfer_buy(int i, int p) {
    ll price = AP[i];
    ll limit = AS[i];
    qh = 0, qt = 0;
    for (int j = 1; j <= MaxP; j++) {
        int nj = j - 1; // 窗口右端新进来的持股数
        ll v = f[p][nj] + price * nj;
        while (qt > qh && f[p][que[qt - 1]] + price * que[qt - 1] <= v)
            qt--; // 值不大于新值的下标从队尾弹出，队列按 g 递减，队头即窗口最大
        que[qt++] = nj;
        int out = j - (int)limit - 1; // 刚滑出窗口左端的持股数；若还在队里必在队头
        if (out >= 0 && que[qh] == out)
            qh++;
        int best = que[qh];
        ll cand = f[p][best] + price * (best - j); // = f[p][best] - price*(j-best)
        if (cand > f[i][j])
            f[i][j] = cand;
    }
}

// 卖出转移：对每个 j，从窗口 j' ∈ [j+1, j+BS] 里取 f[p][j'] + BP*(j'-j) 的最大值写进 f[i][j]
// j 从大到小枚举，窗口整体左移；队列下标递减、g 值递减，队头即窗口最大
void transfer_sell(int i, int p) {
    ll price = BP[i];
    ll limit = BS[i];
    qh = 0, qt = 0;
    for (int j = MaxP - 1; j >= 0; j--) {
        while (qt > qh && que[qh] > j + limit)
            qh++; // 队头是队里最大下标，先滑出窗口右端
        int nj = j + 1; // 窗口左端新进来的持股数
        ll v = f[p][nj] + price * nj;
        while (qt > qh && f[p][que[qt - 1]] + price * que[qt - 1] <= v)
            qt--; // 队尾值不大于新值则弹出（它下标更大、更早过期，被完全压制）
        que[qt++] = nj;
        int best = que[qh];
        ll cand = f[p][best] + price * (best - j); // = f[p][best] + price*(best-j)
        if (cand > f[i][j])
            f[i][j] = cand;
    }
}

int main() {
    scanf("%d %d %d", &T, &MaxP, &W);
    for (int i = 1; i <= T; i++)
        scanf("%lld %lld %lld %lld", &AP[i], &BP[i], &AS[i], &BS[i]);

    // 第 0 天开盘前：0 股 0 钱，其余状态不可达
    for (int j = 1; j <= MaxP; j++)
        f[0][j] = NEG;

    for (int i = 1; i <= T; i++) {
        int p = i - W - 1; // 上次交易最晚发生在第 p 天
        if (p < 0)
            p = 0;
        for (int j = 0; j <= MaxP; j++)
            f[i][j] = f[i - 1][j]; // 当天不交易：原样继承昨天
        if (AS[i] > 0)
            transfer_buy(i, p);
        if (BS[i] > 0)
            transfer_sell(i, p);
    }

    // 结束时持股任意（不交易即 0 股），对...
    ll ans = f[T][0];
    for (int j = 1; j <= MaxP; j++)
        if (f[T][j] > ans)
            ans = f[T][j];
    printf("%lld\n", ans);
    return 0;
}
