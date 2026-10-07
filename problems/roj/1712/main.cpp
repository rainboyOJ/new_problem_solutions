/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:45
 * update_at: 2026-10-07 17:45
 */
// 一本通 1712《汉堡店》
// ---------------------------------------------------------------------------
// 题意：完全图（边权 = 欧氏距离）上选一棵生成树 T，再选 T 中的一条边 (a,b)
//   "吃光"两端，愉悦度 = A / B，其中 A = P_a + P_b，
//   B = T 中除 (a,b) 外其余 N-2 条边的权值和 = W(T) - w(a,b)。求 A/B 最大值。
//
// 推导：
//   固定点对 (a,b)，A 固定，要使 A/B 最大只需让 B 最小，即
//     B_min(a,b) = min_{T ∋ (a,b)} ( W(T) - w(a,b) )
//                = (含边 (a,b) 的最小生成树权值) - w(a,b).
//   记全图 MST 权值为 W。经典替换性质给出
//     含边 (a,b) 的最小生成树权值 = W + w(a,b) - maxEdgeOnMSTPath(a,b),
//   于 是  B_min(a,b) = W - maxEdgeOnMSTPath(a,b).
//   （(a,b) 本身在 MST 上时路径就是这条边，B = W - w(a,b)，与定义一致。）
//
//   接下来不再逐点对枚举，而是用「Kruskal 升序合并」一次性覆盖所有点对：
//   升序加边时，边 e=(u,v) 合并分量 A、B，则所有跨越 A、B 的点对 (u',v')
//   在 MST 上的路径最大边恰为 w(e)（路径上其余边都在更早、更小的权值里）。
//   同一个 w(e) 下，跨分量点对里 P 之和最大的一对就是
//   maxP(A) + maxP(B)。故只需让并查集顺带维护每个分量的 maxP，
//   答案 = max_e ( maxP(A) + maxP(B) ) / ( W - w(e) ).
//
// 复杂度：完全图边数 O(N^2)，排序 O(N^2 log N)，第二遍合并 O(N α)，空间 O(N^2)。
//   N <= 1000 时约 5*10^5 条边，远低于 1000ms / 256MB。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1005;                          // N <= 1000
const int MAXM = MAXN * (MAXN - 1) / 2 + 5;     // 完全图边数上界

struct Point {
    ll x, y;    // 直角坐标
    ll p;       // 美味度 P
};
Point pt[MAXN];

struct Edge {
    int u, v;       // 两个端点
    double w;       // 欧氏距离
};
Edge edge[MAXM];    // 完全图边表
int ecnt;

struct TreeEdge {
    int u, v;       // MST 上的边，保存 Kruskal 的合并顺序（权值升序）
    double w;
};
TreeEdge mst[MAXN]; // MST 恰有 N-1 条边

int fa[MAXN];       // 并查集
ll bestp[MAXN];     // bestp[根] = 该分量里最大的 P

// 按边权升序排序，供 Kruskal 使用
bool cmpEdge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int find(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];  // 路径压缩（隔代压缩，迭代写法避免递归）
        x = fa[x];
    }
    return x;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &pt[i].x, &pt[i].y, &pt[i].p);
    }

    // 建完全图边表：每对点的欧氏距离
    ecnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = (double)(pt[i].x - pt[j].x);
            double dy = (double)(pt[i].y - pt[j].y);
            edge[ecnt].u = i;
            edge[ecnt].v = j;
            edge[ecnt].w = sqrt(dx * dx + dy * dy);
            ecnt++;
        }
    }
    sort(edge, edge + ecnt, cmpEdge);

    // 第一遍 Kruskal：求最小生成树总权值 W，并按合并顺序记下 N-1 条树边
    for (int i = 0; i < n; i++) fa[i] = i;
    double W = 0.0;
    int cnt = 0;
    for (int k = 0; k < ecnt && cnt < n - 1; k++) {
        int a = find(edge[k].u), b = find(edge[k].v);
        if (a == b) continue;       // 已成环，丢掉
        fa[a] = b;
        W += edge[k].w;
        mst[cnt].u = edge[k].u;
        mst[cnt].v = edge[k].v;
        mst[cnt].w = edge[k].w;
        cnt++;
    }

    // 第二遍：按同样的升序合并顺序，维护每个分量的最大 P，边走边更新答案
    for (int i = 0; i < n; i++) {
        fa[i] = i;
        bestp[i] = pt[i].p;
    }
    double ans = 0.0;
    for (int k = 0; k < cnt; k++) {
        int a = find(mst[k].u), b = find(mst[k].v);
        double B = W - mst[k].w;    // 该权值下所有跨分量点对的最小 B
        double cur = (double)(bestp[a] + bestp[b]) / B;
        if (cur > ans) ans = cur;
        // 合并分量，保留较大的 P
        ll merged = bestp[a] > bestp[b] ? bestp[a] : bestp[b];
        fa[a] = b;
        bestp[b] = merged;
    }

    printf("%.2f\n", ans);
    return 0;
}
