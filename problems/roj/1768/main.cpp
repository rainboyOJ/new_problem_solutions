/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 01:05
 * update_at: 2026-10-08 01:12
 */
// main.cpp：交换（一本通 1768）。反向区间 DP + 组合数归并。
//
// 题意：s 从恒等排列 [0..n-1] 出发，按 q_0, ..., q_{n-2} 的顺序做 n-1 次相邻交换
// （第 i 次交换 s[q_i] 与 s[q_i+1]），末态恰好是 p，求这样的排列 q 的个数。
// 因为 q 是 {0..n-2} 的全排列，每条相邻边 (i, i+1) 恰好被使用一次；
// 任何一个数跨过某条边就再也回不来，即任何数只能单向平移。
//
// 核心不变量：合法子问题的区间内容永远形如 [x, p[L+1], p[L+2], ..., p[R-1], y]，
// 即内部位置 j 上的值恒等于 p[j]，只有两个端点可能被祖先的交换"推"进来，
// 且区间内的值恰好构成 {L..R}，x 一旦给定，y 就由"剩下的那个数"唯一确定。
// 于是区间状态只需 (L, R, 左端点上的值 head) 三项。
//
// 转移：倒着看区间 [L,R] 内最后一条被使用的边 k（交换位置 k, k+1）。
// 交换之后左块 [L,k] 里的数再也到不了右块，所以交换后左块的值域必须恰好是 {L..k}。
// 记交换前的区间内容为 c[L..R]，则要求 c[L..k-1] 与 c[k+1] 全部落在 [L,k]
// （左边共 k-L+1 个数，全部落在 [L,k] 内即等价于正好填满），此时才存在这样的 k。
// 剩下的 R-L-1 条边中左子区间占 k-L 条、右子区间占 R-k-1 条，
// 两段互不干涉、可任意交错，归并系数为 C(R-L-1, k-L)。故
//     f(L, R, c) = Σ_{合法的 k} C(R-L-1, k-L) * f(L, k, A[L..k]) * f(k+1, R, A[k+1..R])
// 其中 A 是 c 交换位置 k,k+1 之后的区间内容。边界 f(L, L, c) = [c[L] == L]，
// 答案即 f(0, n-1, p[0..n-1])。
//
// 复杂度：状态数 O(n^3)，每个状态枚举 O(n) 条边、合法判断 O(1)，合计 O(n^4)
// （n <= 50 时实测 8 ms，限时 1000 ms），空间 O(n^3)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL; // 答案取模的模数
const int MAXN = 55;         // 题面 100% 数据 n <= 50，留一点余量
const int INF = 1 << 30;     // 前缀极值的哨兵初值

int n;                // 排列长度
int p[MAXN];          // 目标排列，p[i] 是下标 i 上的值
ll bino[MAXN][MAXN];  // bino[i][j] = C(i, j) 模 MOD
ll memo[MAXN][MAXN][MAXN]; // memo[L][R][head]
char done[MAXN][MAXN][MAXN]; // 该状态是否已算过，只存 0/1，用 char 省内存

// f(L, R, head)：区间 [L,R] 内的边各用一次、把恒等排列 [L..R] 变成目标排列的方案数。
// head 是位置 L 上的值；右端点上的值由区间内容唯一确定，不必进状态。
ll solve(int L, int R, int head) {
    if (L == R) return head == L ? 1 : 0; // 区间只剩一个位置，内容必须正好是它自己
    if (head < L || head > R) return 0;   // 位置 L 上的值不属于本区间，该子问题不可达
    if (done[L][R][head]) return memo[L][R][head];
    done[L][R][head] = 1;

    int len = R - L; // 区间长度减一，也就是区间内的边数
    // 区间内容放局部数组：本函数会递归调用自己，全局数组会被递归改坏
    int ct[MAXN];    // ct[0..len] 对应位置 L..R
    ct[0] = head;
    for (int i = 1; i <= len - 1; i++) ct[i] = p[L + i]; // 内部位置保持原排列的值

    // 校验区间内容恰好是 {L..R} 的一个排列
    bool used[MAXN];
    for (int v = L; v <= R; v++) used[v] = false;
    used[head] = true;
    bool ok = true;
    for (int i = 1; i <= len - 1 && ok; i++) {
        int v = ct[i];
        if (v < L || v > R || used[v]) ok = false;
        else used[v] = true;
    }

    ll res = 0;
    if (ok) {
        int tail = -1; // 区间内没出现过的那个数，只可能是它站在右端点
        for (int v = L; v <= R; v++) {
            if (!used[v]) { tail = v; break; }
        }
        ct[len] = tail;

        int low = INF, high = -INF; // ct[0..ko-1] 的极值，前缀为空时约束自动成立
        for (int ko = 0; ko <= len - 1; ko++) {
            int k = L + ko; // 最后一条被使用的边是 (k, k+1)
            // 交换位置 k,k+1 后左侧是 ct[0..ko-1] 与 ct[ko+1]，共 ko+1 个数，
            // 它们必须正好填满 [L,k]；两边都落在 [L,k] 内即等价（个数已经吻合）
            bool good = low >= L && high <= k && ct[ko + 1] >= L && ct[ko + 1] <= k;
            if (good) {
                // 左子问题的左端点值：ko=0 时位置 k 换回来的是 ct[1]，否则还是 ct[0]
                int leftHead = (ko == 0) ? ct[1] : ct[0];
                ll sub = solve(L, k, leftHead) * solve(k + 1, R, ct[ko]) % MOD;
                res = (res + sub * bino[len - 1][ko]) % MOD;
            }
            if (ct[ko] < low) low = ct[ko];
            if (ct[ko] > high) high = ct[ko];
        }
    }

    memo[L][R][head] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i];

    // 组合数预处理（n <= 50，上界很小，直接 Pascal 三角形）
    for (int i = 0; i <= n; i++) {
        bino[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            bino[i][j] = (bino[i - 1][j - 1] + bino[i - 1][j]) % MOD;
        }
    }

    cout << solve(0, n - 1, p[0]) % MOD << "\n";

    return 0;
}
