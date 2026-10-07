/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:16
 * update_at: 2026-10-08 03:16
 */
// main.cpp：太空飞船（环形序列分成 K 段，最小化各段长度和的"方差"）。
// 关键推导：方差 = Σ(s_i - S/K)^2，两边乘 K^2 得 K^2·Σs_i^2 - K·S^2，
// 于是只需最小化 Σs_i^2，答案 = K^2·minSumSq - K·S^2。
// 与 main.py 同一算法：n 小（<=400）枚举断环起点 + 凸包斜率优化 DP；
// n 大时 K 只可能是 2 或 3，分别用双指针 / 双指针 + 二分处理。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

const ll INF = (ll)4e18;

int N, K;                 // 舱室个数、要分成的段数
ll a[600005];             // 舱室长度；开两倍供断环使用（1-indexed）
ll pre[600005];           // 倍长前缀和：pre[i] = a[1..i] 之和
ll S;                     // 总长度 S = pre[N]

/* ==================== 小数据分支：枚举断环起点 + 斜率优化 ==================== */

ll cur_[405];             // 旋转后的前缀和（把环从 d 处断开）
ll dp[405], ndp[405];     // dp[i]：前 i 个点分成 t 段的最小 Σs^2
ll hm[405], hb[405];      // 凸包上的直线：y = hm*x + hb
int hsz;                  // 凸包大小

// 直线在 x 处的取值
inline ll fval(int id, ll x) { return hm[id] * x + hb[id]; }

// 加一条直线 y = m*x + b。斜率 m 按严格递减的顺序加入（m = -2*cur_[j]）；
// 弹掉被两头夹住的中间直线，保持下凸壳。
void hullAdd(ll m, ll b) {
    while (hsz >= 2) {
        ll m1 = hm[hsz - 2], b1 = hb[hsz - 2];
        ll m2 = hm[hsz - 1], b2 = hb[hsz - 1];
        // 若 line1 与 new 的交点不晚于 line1 与 line2 的交点，则 line2 无用
        if ((b - b1) * (m1 - m2) <= (b2 - b1) * (m1 - m))
            hsz--;
        else
            break;
    }
    hm[hsz] = m;
    hb[hsz] = b;
    hsz++;
}

// 凸包上取值关于下标单峰，二分找最小值
ll hullMin(ll x) {
    int lo = 0, hi = hsz - 1;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (fval(mid, x) <= fval(mid + 1, x))
            hi = mid;
        else
            lo = mid + 1;
    }
    return fval(lo, x);
}

// O(N·K) 斜率优化 DP：对每个断环起点都算一遍
ll solveSmall() {
    ll best = INF;
    for (int d = 1; d <= N; d++) {
        cur_[0] = 0;
        for (int i = 1; i <= N; i++) cur_[i] = cur_[i - 1] + a[d + i - 1];

        dp[0] = 0;
        for (int i = 1; i <= N; i++) dp[i] = INF;

        for (int t = 1; t <= K; t++) {
            hsz = 0;
            for (int i = 1; i <= N; i++) {
                int j = i - 1;  // 先放入 j=i-1，保证查 i 时只用到 j < i
                if (dp[j] < INF)
                    hullAdd(-2 * cur_[j], dp[j] + cur_[j] * cur_[j]);
                ndp[i] = (hsz > 0) ? (hullMin(cur_[i]) + cur_[i] * cur_[i]) : INF;
            }
            for (int i = 0; i <= N; i++) dp[i] = ndp[i];
        }
        best = min(best, dp[N]);
    }
    return best;
}

/* ==================== 大数据分支 K = 2：双指针找最平衡切点 ==================== */

ll solveK2() {
    ll best = INF;
    int j = 1;
    for (int i = 1; i <= N; i++) {
        // j 单调不减：第一段权和不超过 S/2 的最远切点
        while (j <= i + N - 2 && (pre[j + 1] - pre[i - 1]) * 2 <= S) j++;
        for (int d = 0; d <= 1; d++) {  // 切点 j / j+1 分别在 S/2 两侧
            int cut = j + d;
            if (cut < i || cut > i + N - 1) continue;
            ll v = pre[cut] - pre[i - 1];
            best = min(best, v * v + (S - v) * (S - v));
        }
    }
    return best;
}

/* ============ 大数据分支 K = 3：先定第一个切点，再二分第二个切点 ============ */

ll solveK3() {
    ll best = INF;
    int j = 1;
    for (int i = 1; i <= N; i++) {
        // 第一个切点：第一段权和 <= S/3 的最远点 j
        while (j <= i + N - 2 && (pre[j + 1] - pre[i - 1]) * 3 <= S) j++;

        // 第二个切点：在 (j, i+N-2] 内找第二段权和 <= S/3 的最远右端点 l
        int l = j + 1, r = i + N - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if ((pre[mid] - pre[j]) * 3 > S)
                r = mid - 1;
            else
                l = mid;
        }
        // 第二段权和落在 S/3 左右两侧的候选都试一遍（保证三段非空）
        for (int d = -1; d <= 1; d++) {
            int k2 = l + d;
            if (k2 < j + 1 || k2 > i + N - 2) continue;
            ll v1 = pre[j] - pre[i - 1];
            ll v2 = pre[k2] - pre[j];
            ll v3 = S - v1 - v2;
            if (v3 <= 0) continue;
            best = min(best, v1 * v1 + v2 * v2 + v3 * v3);
        }
    }
    return best;
}

int main() {
    if (scanf("%d %d", &N, &K) != 2) return 0;
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &a[i]);
        a[i + N] = a[i];
    }
    for (int i = 1; i <= 2 * N; i++) pre[i] = pre[i - 1] + a[i];
    S = pre[N];

    if (K <= 1) {  // 只有一段，方差恒为 0
        printf("0\n");
        return 0;
    }

    ll minSumSq;
    if (N <= 400)
        minSumSq = solveSmall();          // 精确 DP，K 可到 20
    else if (K == 2)
        minSumSq = solveK2();             // 精确双指针
    else
        minSumSq = solveK3();             // 大数据里 K 只可能是 3

    lll ans = (lll)K * K * minSumSq - (lll)K * S * S;  // __int128 防溢出
    if (ans < 0) {  // 理论上非负，防御性处理
        putchar('-');
        ans = -ans;
    }
    char buf[64];
    int p = 0;
    if (ans == 0) buf[p++] = '0';
    while (ans > 0) {
        buf[p++] = char('0' + (int)(ans % 10));
        ans /= 10;
    }
    while (p > 0) putchar(buf[--p]);
    putchar('\n');
    return 0;
}
