/*
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:53
 * update_at: 2026-10-08 07:53
 */
// main.cpp：ROJ 1788《爬山》，斜率单调链 O(n) + 跳跃树统一累计答案。
//
// 题意：山顶 P_1..P_n 的 x 递增，相邻山顶连成折线 l。站在山顶上时先更新
// 「目前为止见过的最高山顶」T（y 大者更高，y 相同时取 x 大者），再朝 T 的方向
// 走一步（走到相邻山顶），curr == T 时停下。求每个起点的总步数。
//
// 三个关键结论：
//   1) 从 P_i 向右能看到的山顶，其斜率 slope(i,·) 严格递增（否则中间那个点
//      会挡住视线，共线也算挡）。所以「向右能看到的最高点」就是斜率最大的那个
//      可见点，可以用斜率单调链（带路径压缩的跳跃）摊还 O(1) 求出；向左同理。
//      于是每个点张望时看到的最高点只可能是左侧链端 L[i] 或右侧链端 R[i]。
//   2) 朝看到的目标走的过程中不会再冒出更高的点，从 i 会笔直走到 f(i)，
//      即 answer(i) = answer(f(i)) + |i - f(i)|，所有边构成以全局最高点为根的树。
//   3) 不用真的把 f 算出来：按 f 的 (y, x) 秩从小到大处理，用双向链表维护
//      「还没处理过的点」，则 i 在自己前进方向上的最近未处理点 t 就是该走到的
//      落点（中间那些点的秩更小，早被摘掉，路过它们不会转向）。秩单调保证
//      倒序累加步数即可，无需显式建树。

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 500005; // 山顶数上限

int n;                   // 山顶数量
ll px[MAXN], py[MAXN];   // 山顶坐标（x 严格递增）

int Lft[MAXN], Rgt[MAXN];     // 左/右斜率单调链的端点（张望时能看到的最高点）
int seen[MAXN];               // seen[i]：从 P_i 张望看到的最高山顶
int ord[MAXN];                // 按 seen 的 (y, x) 秩升序排列的顶点
int prt[MAXN];                // 跳跃树上的父节点
int lkUp[MAXN], lkDn[MAXN];   // 双向链表：尚未处理的左右邻居
ll ans[MAXN];                 // 每个起点的答案

// 秩比较：y 大者更高；y 相等时 x 大者更高
inline bool higher(int a, int b) {
    return py[a] > py[b] || (py[a] == py[b] && px[a] > px[b]);
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%lld %lld", &px[i], &py[i]);

    // Rgt[i]：右侧斜率单调链的终点。链上斜率严格递增，终点即「向右看到的最高点」。
    for (int i = 0; i < n; i++) Rgt[i] = i + 1;
    Rgt[n - 1] = n - 1;
    for (int i = n - 3; i >= 0; i--) {
        while (Rgt[i] != n - 1) {
            int j = Rgt[i], k = Rgt[j];
            // slope(i, j) < slope(i, k)：中间点挡不住 k，于是直接跳到 k
            if ((py[j] - py[i]) * (px[k] - px[i]) < (py[k] - py[i]) * (px[j] - px[i]))
                Rgt[i] = k;
            else break; // 斜率不再增大：要么 k 被挡，要么与 j 共线（共线也挡）
        }
    }

    // Lft[i]：左侧斜率单调链的终点，尖角朝左，比较公共右端点 i 的两条斜率
    for (int i = 0; i < n; i++) Lft[i] = i - 1;
    Lft[0] = 0;
    for (int i = 2; i < n; i++) {
        while (Lft[i] != 0) {
            int p = Lft[Lft[i]], q = Lft[i];
            // slope(p, i) < slope(q, i)：p 的视线不会被 q 挡，跳到 p（更远处更高）
            if ((py[i] - py[p]) * (px[i] - px[q]) < (py[i] - py[q]) * (px[i] - px[p]))
                Lft[i] = p;
            else break;
        }
    }

    // 左右各只可能贡献一个候选：边界上的点只有一侧有邻居
    for (int i = 0; i < n; i++) {
        if (i == 0) seen[i] = Rgt[0];
        else if (i == n - 1) seen[i] = Lft[n - 1];
        else seen[i] = higher(Lft[i], Rgt[i]) ? Lft[i] : Rgt[i];
    }

    // 全局最高山顶：跳跃树的根，它的答案恒为 0
    int root = 0;
    for (int i = 1; i < n; i++) if (higher(i, root)) root = i;

    // 其余点按「张望目标的秩」升序排列（秩相同的按编号，保证顺序确定）
    int m = 0;
    for (int i = 0; i < n; i++) if (i != root) ord[m++] = i;
    sort(ord, ord + m, [](int a, int b) {
        int ta = seen[a], tb = seen[b];
        if (py[ta] != py[tb]) return py[ta] < py[tb];
        if (px[ta] != px[tb]) return px[ta] < px[tb];
        return a < b;
    });

    // 双向链表 + 跳跃树：已处理的点先从链表里摘掉，于是 i 的最近未处理邻居
    // 就是它该笔直走到的那个山顶，边权即走过的步数
    for (int i = 0; i < n; i++) {
        lkUp[i] = i - 1;
        lkDn[i] = i + 1;
    }
    lkUp[0] = -1;
    lkDn[n - 1] = -1;
    for (int t = 0; t < m; t++) {
        int i = ord[t];
        int nb = (seen[i] < i) ? lkUp[i] : lkDn[i]; // 朝目标那一侧的最近未处理点
        prt[i] = nb;
        if (lkUp[i] != -1) lkDn[lkUp[i]] = lkDn[i];
        if (lkDn[i] != -1) lkUp[lkDn[i]] = lkUp[i];
    }

    // 父节点的秩不低于自己，所以倒序累加：先有父的答案，再算子的答案
    ans[root] = 0;
    for (int t = m - 1; t >= 0; t--) {
        int i = ord[t], p = prt[i];
        ans[i] = ans[p] + (i > p ? i - p : p - i);
    }

    for (int i = 0; i < n; i++) printf("%lld\n", ans[i]);
    return 0;
}
