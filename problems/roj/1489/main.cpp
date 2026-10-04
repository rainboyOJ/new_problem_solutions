/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:05
 * update_at: 2026-10-05 04:05
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

struct Edge {
    ll u;
    ll v;
    ll w;
};

ll n;
Edge edges[MAXN]; // 树的 n-1 条边，读入后按边权升序排序
ll root[MAXN];    // 并查集父点表，下标 0 不用（点编号从 1 开始）
ll size_of[MAXN]; // 块大小：合并时跨两块点对数 = 两块大小之积

// 并查集查根，带路径压缩。
ll find_root(ll x) {
    while (root[x] != x) {
        root[x] = root[root[x]];
        x = root[x];
    }
    return x;
}

// 按边权升序合并连通块，累计所有点对树上路径最大边权之和。
// 合并权为 w 的边时，跨两块的 a*b 个点对路径必经过这条边，
// 且块内已用边权都不超过 w，所以这批点对的路径最大边权恰为 w。
ll pair_max_edge_sum() {
    ll total = 0;
    for (ll i = 1; i <= n - 1; i++) {
        ll ru = find_root(edges[i].u);
        ll rv = find_root(edges[i].v);
        total += edges[i].w * size_of[ru] * size_of[rv];
        root[ru] = rv;
        size_of[rv] += size_of[ru];
    }
    return total;
}

bool cmp_edge(Edge a, Edge b) {
    return a.w < b.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    for (ll i = 1; i <= n; i++) {
        root[i] = i;
        size_of[i] = 1;
    }
    sort(edges + 1, edges + n, cmp_edge); // 按边权升序，即 Kruskal 的合并顺序

    // 每条非树点对的补边最小取"路径最大边权 + 1"，非树点对共 C(n,2) - (n-1) 个
    ll ans = pair_max_edge_sum() + n * (n - 1) / 2 - (n - 1);
    cout << ans << "\n";

    return 0;
}
