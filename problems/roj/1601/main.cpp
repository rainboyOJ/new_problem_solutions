/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:00
 * update_at: 2026-10-05 12:00
 */
// 多重背包恰好凑出 k 的最少硬币数：每种面值一个同余类 + 滑动窗口最小值（单调队列）。

#include <cstdio>

typedef long long ll;

const ll MAXK = 2 * 10 * 1000 + 5; // k <= 2*10^4
const ll INF = 1e9;                // 不可达哨兵（真实答案至多 k，远小于它）

ll n, k;
ll val[205], cnt[205]; // val[i] 第 i 种面值，cnt[i] 该面值的数量上限
ll dp[MAXK];           // dp[v] = 恰好凑出面值 v 的最少硬币数（不可达为 INF）
ll olddp[MAXK];        // 本阶段松弛前的快照：转移只能读上一轮的值
ll que[MAXK];          // 单调队列存同余类内的位置编号 m（0,1,2,...），键 old[r+mw]-m 递增

// 加入面值 w、数量上限 c 的一次有界松弛：把 dp 数组更新为"用前若干种面值"的最优表。
// 按模 w 分同余类，类内第 m 个位置是 v = r + m*w：
//   dp[r+mw] = min_{0<=t<=min(c,m)} ( old[r+(m-t)w] + t )
// 换元 u = m-t 得 dp[r+mw] = m + min_{u in [m-c, m]} ( old[r+uw] - u )，
// 窗口 [m-c, m] 每步右移一格，用单调队列维护键 old[r+uw]-u 的最小值。
void relax_coin(ll w, ll c) {
    if (w > k) return; // 面值超过目标的硬币一枚也用不上，直接跳过这一阶段
    for (ll r = 0; r < w; r++) { // 同余类之间互不干扰，一条一条做
        ll head = 1, tail = 0;   // 队列区间 [head, tail]，空队列 head > tail
        for (ll m = 0; r + m * w <= k; m++) {
            ll pos = r + m * w;
            ll key = olddp[pos] - m; // 候选下标 u=m 的键
            while (head <= tail && olddp[r + que[tail] * w] - que[tail] >= key)
                tail--;              // 队尾键不更小，以后永远轮不到当最小值，弹出
            que[++tail] = m;         // 当前位置入队
            while (m - que[head] > c) // 队首滑出窗口 [m-c, m]，数量上限在这里生效
                head++;
            dp[pos] = m + olddp[r + que[head] * w] - que[head];
        }
    }
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) scanf("%lld", &val[i]);
    for (ll i = 1; i <= n; i++) scanf("%lld", &cnt[i]);
    scanf("%lld", &k);

    for (ll v = 1; v <= k; v++) dp[v] = INF; // 一开始只有 0 面值可达
    dp[0] = 0;

    for (ll i = 1; i <= n; i++) {
        for (ll v = 0; v <= k; v++) olddp[v] = dp[v]; // 松弛前先取快照
        relax_coin(val[i], cnt[i]);
    }

    printf("%lld\n", dp[k]);
    return 0;
}
