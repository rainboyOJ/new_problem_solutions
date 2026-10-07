/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:13
 * update_at: 2026-10-08 03:13
 */
// 1790《序列划分》
// ---------------------------------------------------------------------------
// 题意：给定 n 个数对 (a_i,b_i) 与正整数 m，把序列切成连续若干段，满足
//   ① 若 i<j 且 i、j 不在同一段中，则 b_i > a_j；
//   ② 每一段的 a 的最大值之和 ≤ m；
//   在此基础上最小化「每一段的 b 的值之和」的最大值。
//
// 关键转化 1（切点合法性的刻画）：
//   切在 c 与 c+1 之间（记切点为 c，1≤c<n）合法 ⟺ min_{i≤c} b_i > max_{j>c} a_j。
//   证明：若该不等式成立，取分处两段的 i<j，必有切点 c 使 i≤c<j，于是
//         b_i ≥ min_{i'≤c} b_{i'} > max_{j'>c} a_{j'} ≥ a_j，条件①满足；
//         反之若某切点 c 不满足，取 i*=argmin_{i≤c} b_i、j*=argmax_{j>c} a_j，
//         则 i*<j* 分处两段且 b_{i*} ≤ a_{j*}，条件①被破坏。
//   于是「合法划分」=「只使用合法切点的划分」，合法切点集唯一确定。
//
// 关键转化 2（原子段压缩）：
//   按合法切点把序列压成若干个连续的「原子段」，每段记录 A=max a、B=Σ b。
//   任何合法划分都是一个接一个地把连续原子段并成块。
//
// 主算法（二分答案 + 单调队列 + multiset）：
//   二分答案 X（= 每段 b 之和的上限）。判定 check(X)：在「每块 B 之和 ≤ X」下
//   求 Σ max(A) 的最小值 g[s]，看是否 ≤ m。转移
//       g[i] = min_{j∈[L_i-1, i-1]} ( g[j] + max(A[j+1..i]) )，
//   其中 L_i 由 B 的双指针给出（最小合法起点）。由于 A ≥ 1 时 g 单调不降，
//   且后缀最大值随 j 左移单调不降（阶梯），可用单调递减队列维护阶梯：
//   队内相邻两项界定一个阶梯，阶梯内最优转移点必是最左端（g 单调）。
//   阶梯候选值 = g[队内前驱] + A[队内元素]，除队首外放入 multiset；
//   队首阶梯的左端点是游标 L-1，转移时现算 g[L-1] + A[队首]。
//   g[i] = min( g[L-1]+A[队首], multiset 最小值 )。单次判定 O(s log s)。
// ---------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const ll INF = (ll)1e17;   // 真值上界 Σmax(a) ≤ 1e5·2e9 = 2e14

int n, s;                  // n 原序列长度；s 原子段个数
ll m;
ll a[MAXN], b[MAXN];       // 原序列（1 下标）
ll A[MAXN], B[MAXN];       // 原子段（1 下标）
ll PB[MAXN];               // 原子段 B 的前缀和
ll sufA[MAXN];             // 原序列 a 的后缀最大值
ll dp[MAXN];               // 判定用的 DP
int dq[MAXN];              // 单调队列（存原子段下标）
ll cand[MAXN];             // cand[k] = dp[dq[k-1]] + A[dq[k]]，k 不是队首时有效

// 判定：是否存在划分使每块 B 之和 ≤ X 且 Σmax(A) ≤ m
bool check(ll X) {
    multiset<ll> ms;
    int h = 0, t = 0, L = 1;
    ll sum = 0;
    dp[0] = 0;
    for (int i = 1; i <= s; i++) {
        dp[i] = INF;
        sum += B[i];
        while (sum > X) { sum -= B[L]; L++; }        // L = 最小合法左端点
        // 队首对应的阶梯整体滑出窗口：出队并同步删除次队首的候选值
        while (h < t && dq[h] < L) {
            if (t - h >= 2) ms.erase(ms.find(cand[h + 1]));
            h++;
        }
        // 队尾被 A[i] 压住的阶梯合并（这些元素不可能再成为任何后缀最大值）
        while (h < t && A[dq[t - 1]] <= A[i]) {
            if (t - 1 > h) ms.erase(ms.find(cand[t - 1]));
            t--;
        }
        // i 入队：它是新的最右阶梯，候选值为 dp[前驱] + A[i]
        if (t > h) { cand[t] = dp[dq[t - 1]] + A[i]; ms.insert(cand[t]); }
        dq[t++] = i;
        // 队首阶梯左端点随 L 游走，单独现算；其余阶梯取 multiset 最小值
        ll best = dp[L - 1] + A[dq[h]];
        if (!ms.empty()) best = min(best, *ms.begin());
        dp[i] = best;
    }
    return dp[s] <= m;
}

int main() {
    if (scanf("%d %lld", &n, &m) != 2) {
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &a[i], &b[i]);
    }

    // 原始 a 的后缀最大值
    sufA[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        sufA[i] = max(sufA[i + 1], a[i]);
    }

    // 按合法切点压缩成原子段
    s = 0;
    ll mx = 0, sm = 0;
    ll pre = LLONG_MAX;       // 前缀 min b，只需一个游标变量
    for (int i = 1; i <= n; i++) {
        mx = max(mx, a[i]);
        sm += b[i];
        pre = min(pre, b[i]);
        if (i == n || pre > sufA[i + 1]) {           // i 与 i+1 之间可切
            ++s;
            A[s] = mx;
            B[s] = sm;
            mx = 0;
            sm = 0;
        }
    }
    PB[0] = 0;
    for (int i = 1; i <= s; i++) {
        PB[i] = PB[i - 1] + B[i];
    }

    ll lo = 0, hi = PB[s];
    for (int i = 1; i <= s; i++) {
        lo = max(lo, B[i]);
    }

    if (!check(hi)) {          // Σmax(a) 的最小值就是整体一段的 max a > m，无解
        printf("-1\n");
        return 0;
    }
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    printf("%lld\n", lo);
    return 0;
}
