/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:05
 * update_at: 2026-10-07 21:05
 *
 * 一本通 1749《矩阵求和》
 *
 * 关键恒等变换：C[i][j] = A[i]*B[j] + i*B[j] + A[i]*j + i*j = (A[i]+i)*(B[j]+j)。
 * 令 X[i] = A[i]+i, Y[j] = B[j]+j，由于 0 <= A,B 且下标从 1 起，X、Y 恒正，
 * 于是 k*k 子矩阵的最大值 = 行窗 X 最大值 * 列窗 Y 最大值，行列互不影响：
 *     F[k] = (所有长度 k 的 X 窗最大值之和) * (所有长度 k 的 Y 窗最大值之和)。
 * 剩下的子问题「所有长度 k 子区间最大值之和」用单调栈统计每个元素作为
 * 最右最大值时的贡献区间数，贡献数关于 k 分段线性，用两个差分数组一次求出全部 k。
 * 时间 O(n)，空间 O(n)。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;
const int MAXN = 100005;

ll a[MAXN], b[MAXN];
ll x[MAXN], y[MAXN];    // x[i] = a[i] + i, y[i] = b[i] + i
int lef[MAXN], rig[MAXN]; // 左侧最近的严格更大位置、右侧最近的大于等于位置
int stk[MAXN];            // 单调栈，存下标
ll slope[MAXN];           // 差分数组：k 的系数
ll constant[MAXN];        // 差分数组：常数项
ll sx[MAXN], sy[MAXN];    // 两个数组的「长度 k 窗最大值之和」

// 对差分数组 d 在区间 [l, r] 上加 v（v 已对 MOD 取模）
void add_range(ll d[], int l, int r, ll v) {
    if (l > r || v == 0) return;
    d[l] = (d[l] + v) % MOD;
    d[r + 1] = (d[r + 1] - v + MOD) % MOD;
}

// 求 arr 所有长度 k 子区间最大值之和，k = 1..n，结果对 MOD 取模写入 out[1..n]
void window_max_sum(ll arr[], int n, ll out[]) {
    // 左侧最近的严格大于 arr[i] 的位置（无则 0）
    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top > 0 && arr[stk[top]] <= arr[i]) top--;
        lef[i] = (top > 0) ? stk[top] : 0;
        stk[++top] = i;
    }
    // 右侧最近的大于等于 arr[i] 的位置（无则 n+1）
    top = 0;
    for (int i = n; i >= 1; i--) {
        while (top > 0 && arr[stk[top]] < arr[i]) top--;
        rig[i] = (top > 0) ? stk[top] : n + 1;
        stk[++top] = i;
    }

    for (int i = 0; i <= n + 1; i++) {
        slope[i] = 0;
        constant[i] = 0;
    }

    // 记 a = i - lef[i]，b = rig[i] - i。arr[i] 恰是区间 [s,e] 的最右最大值
    // 当且仅当 lef[i] < s <= i <= e < rig[i]，故它被长度 k 的区间计入的次数
    //     cnt(k) = min(k, a, b, a+b-k)   (1 <= k <= a+b-1)
    // 该函数关于 k 分三段线性：k 段、常数 m 段、a+b-k 段。
    for (int i = 1; i <= n; i++) {
        ll v = arr[i] % MOD;
        int a = i - lef[i];
        int b = rig[i] - i;
        int m = min(a, b);
        int big = max(a, b);
        int last = a + b - 1;              // cnt(k) > 0 的最大 k
        add_range(slope, 1, m, v);                          // cnt = k
        add_range(constant, m + 1, big, v * m % MOD);       // cnt = m
        add_range(constant, big + 1, last, v * ((a + b) % MOD) % MOD); // cnt = a+b-k
        add_range(slope, big + 1, last, (MOD - v) % MOD);
    }

    // 前缀和还原出 f(k) = (斜率前缀) * k + (常数前缀)
    ll s1 = 0, s2 = 0;
    for (int k = 1; k <= n; k++) {
        s1 = (s1 + slope[k]) % MOD;
        s2 = (s2 + constant[k]) % MOD;
        out[k] = (s1 * (k % MOD) + s2) % MOD;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i <= n; i++) {
        if (scanf("%lld", &a[i]) != 1) return 0;
        x[i] = a[i] + i;
    }
    for (int i = 1; i <= n; i++) {
        if (scanf("%lld", &b[i]) != 1) return 0;
        y[i] = b[i] + i;
    }

    window_max_sum(x, n, sx);
    window_max_sum(y, n, sy);

    for (int k = 1; k <= n; k++) {
        ll ans = sx[k] * sy[k] % MOD;
        if (k < n) printf("%lld ", ans);
        else printf("%lld\n", ans);
    }
    return 0;
}
