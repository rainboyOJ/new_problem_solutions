/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-05 12:07
 */
// 烽火传递：单调队列优化的线性 DP。
// 约束等价于「相邻两座点火台的距离不超过 m，且最后一座离 n 不超过 m-1」，
// 于是 dp[i] = a[i] + min(dp[i-m .. i-1])，答案是 min(dp[n-m+1 .. n])。
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

ll a[MAXN];    // a[i] 第 i 座烽火台发出信号的代价
ll dp[MAXN];   // dp[i] 表示第 i 座必须点火、且前缀 1..i 已满足约束时的最小代价
ll que[MAXN];  // 单调队列，存下标；对应的 dp 值自队首到队尾严格递增
int head, tail; // 队列区间 [head, tail)，队首 que[head] 即窗口最小值所在下标

int main() {
    ll n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 下标 0 是虚拟哨兵，dp[0] = 0，负责 i <= m 时「前面一座都不点火」的情形
    dp[0] = 0;
    head = 0;
    tail = 0;
    que[tail++] = 0;

    for (int i = 1; i <= n; i++) {
        while (head < tail && que[head] < i - m) {
            head++; // 队首已经滑出窗口左界 i-m，不能再作为转移来源
        }
        dp[i] = dp[que[head]] + a[i];
        // 更晚进队却更优的旧下标永远不会再成为最小值，直接淘汰
        while (head < tail && dp[que[tail - 1]] >= dp[i]) {
            tail--;
        }
        que[tail++] = i;
    }

    // 尾部豁免：最后一座点火台 t 只需满足 n - t <= m-1，即 t >= n-m+1，
    // 所以答案不是 dp[n]。下界与 1 取大，兼顾 m > n 时退化为选最便宜的一座
    ll low = max(1LL, n - m + 1);
    while (head < tail && que[head] < low) {
        head++;
    }
    printf("%lld\n", dp[que[head]]);
    return 0;
}
