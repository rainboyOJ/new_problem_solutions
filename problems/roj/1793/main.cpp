/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:30
 * update_at: 2026-10-08 03:30
 */

// 一本通 1793《鏖战字符串》
// 题意：给出长度 n 的字符串与每个位置的删除难度 dif[i]（0 <= dif[i] <= 50）。
//   要把前缀 [1,i] 切成若干连续子串，每个子串二选一删除：
//     ① 代价 a*x^2 + b                    （x = 子串内 dif 之和）
//     ② 代价 c*x + d，当且仅当子串中出现次数最多的字符出现次数 ∈ [l, r]
//   求删去每个前缀 [1,i] 的最少用时，输出 n 行。
//
// 算法（O(n)）：
//   pre[i] = sum_{k<=i} dif[k]（因 dif >= 0，pre 单调不减），dp[0] = 0。
//   dp[i] = min_{0<=j<i} { dp[j] + cost(j+1, i) }，
//   cost(j+1,i) = min( a*X^2 + b , [maxfreq(j+1,i) ∈ [l,r]] * (c*X + d) )，X = pre[i]-pre[j]。
//
//   (A) 方法① —— 斜率优化（下凸壳）：
//       dp[j] + a*(pre[i]-pre[j])^2 + b = a*pre[i]^2 + b + ( dp[j] + a*pre[j]^2 ) - 2a*pre[i]*pre[j]
//       点 (X_j, Y_j) = (pre[j], dp[j] + a*pre[j]^2)，查询斜率 K_i = 2a*pre[i]。
//       X_j 与 K_i 都随 i 单调不减 => 维护下凸壳 + 单调队列，均摊 O(1) 查一次。
//
//   (B) 方法② —— 频次窗口 + 滑动窗口最小值：
//       固定 i，maxfreq(j+1, i) 随 j 增大单调不增（窗口变短）。
//       于是「maxfreq >= l」的 j 构成前缀 j <= sL-1，「maxfreq <= r」的 j 构成后缀 j >= sR，
//       合法集合是连续区间 [sR, sL-1]（l > r 时为空，方法② 自动失效，退化为纯 (A)）。
//       sL = max_c ( 字符 c 第 (cnt_c-l+1) 次出现的位置 )，sR = max_c ( 第 (cnt_c-r) 次出现的位置，不足取 0 )；
//       两者都随 i 单调不减，故 [sR, sL-1] 是双指针维护的滑动窗口。
//       区间内最小化 dp[j] - c*pre[j]（与 i 无关）用单调队列，均摊 O(1)。
//
//   复杂度 O(n) 时间、O(n) 空间。中间量最大约 233 * (50*1e5)^2 ≈ 5.8e15，long long 安全。
//   dif[i] = 0 时会出现 pre[j] == pre[j-1]（横坐标重合），凸壳入队时单独去重，不能直接除斜率。

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef __int128 lll;

const int MAXN = 100005;

ll n;              // 字符串长度
ll A, B, C, D;     // 题面的 a, b, c, d
ll LNEED, RNEED;   // 题面的 l, r
char str_[MAXN];   // 字符串，1-based
ll dif[MAXN];      // dif[i]：第 i 个字符的删除难度
ll pre[MAXN];      // pre[i]：前缀 [1,i] 的删除难度之和
ll dp[MAXN];       // dp[i]：删去前缀 [1,i] 的最少用时

int occ[26][MAXN]; // occ[ch][k]：字符 ch 第 k 次出现的位置（1-based，k 从 1 开始）
int cnt[26];       // cnt[ch]：字符 ch 到目前为止的出现次数

// ---- 方法①：斜率优化（下凸壳）用的单调队列，存决策点下标 j ----
int hull[MAXN];
int hh, ht;        // 凸壳区间为 [hh, ht)

// 凸壳上决策点 j 的纵坐标 Y_j = dp[j] + a*pre[j]^2
ll yval(int j) {
    return dp[j] + A * pre[j] * pre[j];
}

// 下凸壳维护：slope(p,q) >= slope(q,r) 时 q 冗余（交叉相乘，避免除法与浮点误差）
bool hull_bad(int p, int q, int r) {
    lll lhs = (lll)(yval(q) - yval(p)) * (pre[r] - pre[q]);
    lll rhs = (lll)(yval(r) - yval(q)) * (pre[q] - pre[p]);
    return lhs >= rhs;
}

// 把决策点 j 插入下凸壳
void hull_add(int j) {
    if (ht > hh && pre[hull[ht - 1]] == pre[j]) { // 横坐标重合（dif 出现 0），只留 Y 更小者
        if (yval(hull[ht - 1]) <= yval(j)) return;
        ht--;
    }
    while (ht - hh >= 2 && hull_bad(hull[ht - 2], hull[ht - 1], j)) ht--;
    hull[ht++] = j;
}

// 查询斜率 K 下的最优决策点；K 随 i 单调不减，队头只往后走，均摊 O(1)
int hull_best(ll K) {
    while (ht - hh >= 2) {
        int j0 = hull[hh], j1 = hull[hh + 1];
        if (yval(j0) - K * pre[j0] >= yval(j1) - K * pre[j1]) hh++;
        else break;
    }
    return hull[hh];
}

// ---- 方法②：滑动窗口最小值的单调队列，存下标 j，按 dp[j]-c*pre[j] 递增 ----
ll win[MAXN];
int wh, wt;

int main() {
    if (scanf("%lld %lld %lld %lld %lld %lld %lld", &n, &A, &B, &C, &D, &LNEED, &RNEED) != 7) return 0;
    scanf("%s", str_ + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &dif[i]);
        pre[i] = pre[i - 1] + dif[i]; // dif >= 0，pre 单调不减
    }

    dp[0] = 0;
    ll sL = 0, sR = 0; // 合法决策区间为 [sR, sL-1]
    ll pushed = -1;    // win 中已推入的最大下标

    for (int i = 1; i <= n; i++) {
        int ch = str_[i] - 'a';
        cnt[ch]++;
        occ[ch][cnt[ch]] = i;

        // 更新 sL：字符 ch 第 (cnt-l+1) 次出现的位置，说明以它为左端点的窗口装得下 >= l 个 ch
        ll k1 = cnt[ch] - LNEED + 1;
        if (k1 >= 1 && occ[ch][k1] > sL) sL = occ[ch][k1];
        // 更新 sR：字符 ch 第 (cnt-r) 次出现的位置，左端点越过它后 ch 的出现次数必 <= r
        ll k2 = cnt[ch] - RNEED;
        if (k2 >= 1 && occ[ch][k2] > sR) sR = occ[ch][k2];

        // 右端点 sL-1 单调不减，逐个把新决策点推入单调队列
        while (pushed < sL - 1) {
            pushed++;
            ll hv = dp[pushed] - C * pre[pushed];
            while (wt > wh && dp[win[wt - 1]] - C * pre[win[wt - 1]] >= hv) wt--;
            win[wt++] = pushed;
        }
        // 左端点 sR 单调不减，弹出过期决策点（sR > sL-1 时队列会被清空，方法② 失效）
        while (wt > wh && win[wh] < sR) wh++;

        hull_add(i - 1);                    // 决策点 j = i-1 此刻的 dp 已确定，先入凸壳再查询
        int j1 = hull_best(2 * A * pre[i]); // 方法①的最优分割点
        ll best = dp[j1] + A * (pre[i] - pre[j1]) * (pre[i] - pre[j1]) + B;

        if (wt > wh) { // 方法②可用：区间 [sR, sL-1] 非空
            ll j2 = win[wh];
            ll cand = dp[j2] - C * pre[j2] + C * pre[i] + D;
            if (cand < best) best = cand;
        }

        dp[i] = best;
        printf("%lld\n", dp[i]);
    }
    return 0;
}
