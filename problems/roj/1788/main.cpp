/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 08:10
 * update_at: 2026-10-08 08:10
 */
// main.cpp：ROJ 1788《爬山》。
// 与 main.py 同一算法：先 O(n) 求出每个山顶真正能看到的最高山顶 f[i]，
// 再用"单调栈求首个更高者"定出每个山顶在最优路径上的下一站 par[i]，
// 最后沿 par 链把步数累加起来，全程 O(n)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;   // 山顶数上限 5e5

int N;                     // 山顶个数
int X[MAXN], Y[MAXN];      // 山顶坐标，X 严格递增
int Rj[MAXN], Lj[MAXN];    // 向右 / 向左能看到的最远山顶（即斜率最大者）
int f[MAXN];               // f[i]：山顶 i 看得到的最高山顶（等高取 x 大者）
int nxt[MAXN], prv[MAXN];  // 首个 f 值比 i 更大 的右侧 / 左侧山顶
int par[MAXN];             // 最优路径上 i 的下一站
int stk[MAXN], path[MAXN]; // 单调栈、沿 par 链回溯时的路径
ll ans[MAXN];              // 答案：从 i 出发走过的边数（-1 表示还没算出）

// 把"山顶的优劣"压成一个整数键：先比 y，y 相同再比 x，越大越高
inline ll key(int p) { return (ll)Y[f[p]] * 1000001 + X[f[p]]; }

// a 是否严格比 b 高：y 大者高，y 相同取 x 大者
inline bool rankBetter(int a, int b) {
    return Y[a] > Y[b] || (Y[a] == Y[b] && X[a] > X[b]);
}

// slope(i,j) < slope(i,k)，左右端点全部交叉相乘，不出现除法
inline bool slopeLt(int i, int j, int k) {
    return (ll)(Y[j] - Y[i]) * (X[k] - X[i]) < (ll)(Y[k] - Y[i]) * (X[j] - X[i]);
}

// slope(p,i) < slope(q,i)，公共右端点 i（向左看时用）
inline bool slopeLt2(int p, int q, int i) {
    return (ll)(Y[i] - Y[p]) * (X[i] - X[q]) < (ll)(Y[i] - Y[q]) * (X[i] - X[p]);
}

int main() {
    if (scanf("%d", &N) != 1) return 0;
    for (int i = 0; i < N; i++) scanf("%d %d", &X[i], &Y[i]);

    if (N == 1) { printf("0\n"); return 0; }

    // 全局最高山顶：y 大者优先，y 相同取 x 大者
    int hi = 0;
    for (int i = 1; i < N; i++)
        if (rankBetter(i, hi)) hi = i;

    // ① Rj[i]：从 i 向右看的斜率最大者，也就是 i 向右能看到的最高山顶。
    //    从右往左扫，Rj 用"斜率严格递增就继续往右跳"的链式加速。
    for (int i = 0; i < N; i++) Rj[i] = i + 1;
    Rj[N - 1] = N - 1;
    for (int i = N - 3; i >= 0; i--)
        while (Rj[i] != N - 1 && slopeLt(i, Rj[i], Rj[Rj[i]]))
            Rj[i] = Rj[Rj[i]];

    // ② Lj[i]：从 i 向左看的斜率最大者，同理（从左往右扫）
    for (int i = 0; i < N; i++) Lj[i] = i - 1;
    Lj[0] = 0;
    for (int i = 2; i < N; i++)
        while (Lj[i] != 0 && slopeLt2(Lj[Lj[i]], Lj[i], i))
            Lj[i] = Lj[Lj[i]];

    // ③ f[i]：i 能看到的最高的山 = {i, 左侧斜率最大者, 右侧斜率最大者} 中 rank 最高者
    for (int i = 0; i < N; i++) {
        if (i == hi) { f[i] = hi; continue; }
        int cand = i;                                  // 先拿自己当基准（两侧都被挡住时退回自己）
        if (i > 0 && rankBetter(Lj[i], cand)) cand = Lj[i];
        if (i < N - 1 && rankBetter(Rj[i], cand)) cand = Rj[i];
        f[i] = cand;
    }

    // ④ nxt[i] / prv[i]：首个"f 值严格大于 f[i]"的山顶（单调栈 O(n)）
    for (int i = N - 1, top = 0; i >= 0; i--) {
        while (top && key(stk[top - 1]) <= key(i)) top--;
        nxt[i] = top ? stk[top - 1] : -1;
        stk[top++] = i;
    }
    for (int i = 0, top = 0; i < N; i++) {
        while (top && key(stk[top - 1]) <= key(i)) top--;
        prv[i] = top ? stk[top - 1] : -1;
        stk[top++] = i;
    }

    // ⑤ par[i]：走向 f[i] 的途中，第一个"能看到更高山顶"的位置才是真正的转向点；
    //    如果沿途都没人能看得更高，就一口气走到 f[i]。
    for (int i = 0; i < N; i++) {
        if (i == hi) { par[i] = hi; continue; }
        int v = f[i];
        if (v > i) {
            int k = nxt[i];
            par[i] = (k != -1 && k < v) ? k : v;
        } else {
            int k = prv[i];
            par[i] = (k != -1 && k > v) ? k : v;
        }
    }

    // ⑥ 沿 par 链递推：ans[i] = |i - par[i]| + ans[par[i]]。
    //    每条链的终点都是全局最高峰 hi，且链上答案只会被算一次，总代价 O(N)。
    for (int i = 0; i < N; i++) ans[i] = -1;
    ans[hi] = 0;
    for (int i = 0; i < N; i++) {
        if (ans[i] >= 0) continue;
        int len = 0, cur = i;
        while (ans[cur] < 0) { path[len++] = cur; cur = par[cur]; }  // 先走到已知答案处
        ll base = ans[cur];
        while (len--) {                                             // 再倒着把路径填回去
            cur = path[len];
            base += (cur > par[cur] ? cur - par[cur] : par[cur] - cur);
            ans[cur] = base;
        }
    }

    for (int i = 0; i < N; i++) printf("%lld\n", ans[i]);
    return 0;
}
