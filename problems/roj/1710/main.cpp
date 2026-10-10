/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:32
 * update_at: 2026-10-07 17:32
 */

// 构造完全图（一本通 1710）
// 给一棵树 T，求以 T 为唯一最小生成树的完全图 G 的最小边权和。
//
// 算法（Kruskal 思想 + 并查集，O(N log N)）：
//   把 N-1 条树边按权值 w 从小到大排序，依次用并查集合并两端所在连通块。
//   合并前两块大小分别为 sx、sy，则跨两块的点对共 sx*sy 条：
//     其中 1 条就是当前这条树边（权 w，已计入答案），
//     其余 sx*sy-1 条在完全图里必须 >= w+1，否则最小生成树就不唯一了；
//     取 w+1 时恰好可行（该权值下跨块的唯一最轻边仍是这条树边）。
//   故每条树边贡献 w + (sx*sy-1)*(w+1)，合并后 size 相加。
//
//   唯一性论证：Kruskal 按权值升序扫时，处理到权 w 的树边时它两端连通块之间
//   所有非树边权值都 > w（构造取 w+1），所以每条树边都被严格地"抢先"选中，
//   不存在权值相等的替代边，T 是唯一的 MST。
//
// 数据范围：N <= 100000，1 <= D_i <= 100000。
// 答案量级最坏约 n^2/2 * 1e5 ≈ 5e14，超 32 位，全程用 long long。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 点数上限

struct Edge {
    ll u; // 端点
    ll v; // 端点
    ll w; // 边权
};
Edge edge[MAXN]; // N-1 条树边，排序后按权值升序处理

ll fa[MAXN];  // 并查集父亲
ll siz[MAXN]; // 连通块点数：跨块点对数是它俩的乘积，答案里要乘 w+1

ll n;   // 点数
ll ans; // 答案：所有树边权值 + 补出来的非树边权值

bool cmp_edge(const Edge &a, const Edge &b) { return a.w < b.w; }

// 并查集找根，带路径压缩（迭代写法，链深 1e5 也不会爆栈）
ll find_root(ll x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

void solve() {
    scanf("%lld", &n);

    ans = 0;
    for (ll i = 1; i <= n - 1; i++) {
        scanf("%lld%lld%lld", &edge[i].u, &edge[i].v, &edge[i].w);
        ans += edge[i].w; // 树边本身全部出现在完全图里，先全额计入
    }

    sort(edge + 1, edge + n, cmp_edge); // 注意右端点是 edge+n：只需排前 n-1 条

    for (ll i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }

    for (ll i = 1; i <= n - 1; i++) {
        ll a = find_root(edge[i].u);
        ll b = find_root(edge[i].v);
        ll sx = siz[a];
        ll sy = siz[b];
        // 跨两块共 sx*sy 条边，扣掉 1 条树边，剩下的每条最少 w+1
        ans += (sx * sy - 1) * (edge[i].w + 1);
        if (sx < sy) { // 小树挂大树，保证路径压缩的效率
            fa[a] = b;
            siz[b] = sx + sy;
        } else {
            fa[b] = a;
            siz[a] = sx + sy;
        }
    }

    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
