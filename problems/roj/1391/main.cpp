/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:30
 * update_at: 2026-10-05 12:30
 */

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXK = 10005; // n<=100，最多 n*(n-1)/2 条边，开大一倍留余量

struct Edge {
    ll w; // 通畅程度，越小越通畅
    ll u;
    ll v;
};

Edge edge[MAXK]; // 保存所有网线，Kruskal 按 w 升序扫描

ll parent[105]; // 并查集：parent[x] 表示 x 所在集合的父节点

// 返回 x 所在集合的根，路径压缩
ll find_root(ll x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

// Kruskal 的排序标准：按通畅程度升序
bool cmp_edge(Edge a, Edge b) {
    return a.w < b.w;
}

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);

    ll total = 0; // 所有网线通畅程度之和，是常数部分
    for (ll e = 1; e <= k; e++) {
        scanf("%lld %lld %lld", &edge[e].u, &edge[e].v, &edge[e].w);
        total = total + edge[e].w;
    }
    sort(edge + 1, edge + k + 1, cmp_edge);

    for (ll i = 1; i <= n; i++) {
        parent[i] = i; // 初始时每台计算机自成一个集合
    }

    ll keep = 0;  // 最小生成树的权值和
    ll used = 0;  // 已并入生成树的边数，达到 n-1 时全图已连通
    for (ll e = 1; e <= k; e++) {
        ll ru = find_root(edge[e].u);
        ll rv = find_root(edge[e].v);
        if (ru == rv) {
            continue; // 两端已连通，留下这条边会成环，必须删掉
        }
        parent[ru] = rv;
        keep = keep + edge[e].w;
        used++;
        if (used == n - 1) {
            break;
        }
    }

    // 删边权和最大 = 总权值和 - 保留的最小权值和
    printf("%lld\n", total - keep);
    return 0;
}
