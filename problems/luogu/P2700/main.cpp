/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 21:40
 * update_at: 2026-10-21 21:40
 */
// P2700 逐个击破
// 正难则反：直接想「删掉哪些边代价最小」要同时照顾所有敌城，很难；翻转成
// 「尽量多保留边，使代价和最大」，答案 = 总边权 - 最大保留边权。
// 保留的边构成森林，要求：每个连通块里至多有一个敌城。
//
// 贪心做法（本质是 Kruskal）：按边权从大到小扫，能用（不会把两个含敌城的块粘在一起）
// 就保留（不花钱），不能用就必须破坏（付这条边的代价）。
// 正确性直觉：重边先决定，任何偏离都只能拿更轻的边来换，不会更优。
//
// 复杂度：排序 O(n log n) + 并查集近似 O(n α(n))，空间 O(n)。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100000 + 5;  // 城市数上限 N <= 1e5

struct Edge {
    int u;   // 公路一端
    int v;   // 公路另一端
    ll w;    // 破坏这条公路的代价
};
Edge edge[MAXN];  // edge[1..n-1]：树上的 n-1 条公路

int dsu_parent[MAXN];  // dsu_parent[x]：x 的父亲，x 是根时等于 x
int dsu_size[MAXN];    // dsu_size[x]：x 是根时这个连通块的城市数
bool has_enemy[MAXN];  // has_enemy[根]：这个连通块里有没有被敌军占领的城市

// 边权大的排在前面：先决定最贵的边留不留，符合「重边优先」。
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

// 找 x 所在集合的根，顺路把路径上的点直接挂到根上（路径压缩）。
int dsu_find(int x) {
    if (dsu_parent[x] == x) return x;
    dsu_parent[x] = dsu_find(dsu_parent[x]);
    return dsu_parent[x];
}

// 合并 a、b 所在的两个集合，返回合并后的根；两端本来就连通时返回 -1。
// dsu_size[x] 是 x 当根时集合的城市数，用来按大小合并。
int dsu_merge(int a, int b) {
    int root_a = dsu_find(a);
    int root_b = dsu_find(b);
    if (root_a == root_b) return -1;
    // 小集合并到大集合下面，配合路径压缩，单次操作接近常数。
    if (dsu_size[root_a] < dsu_size[root_b]) swap(root_a, root_b);
    dsu_parent[root_b] = root_a;
    dsu_size[root_a] += dsu_size[root_b];
    return root_a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 城市编号从 0 开始，并查集也按 0..n-1 开
    for (int i = 0; i < n; i++) {
        dsu_parent[i] = i;
        dsu_size[i] = 1;
        has_enemy[i] = false;
    }

    // 标记被敌军占领的城市
    for (int i = 1; i <= k; i++) {
        int city;
        cin >> city;
        has_enemy[city] = true;
    }

    for (int i = 1; i <= n - 1; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
    sort(edge + 1, edge + n, cmp_edge);  // edge[1 .. n-1] 按代价降序

    ll answer = 0;  // 累加必须破坏的公路代价
    for (int i = 1; i <= n - 1; i++) {
        int root_u = dsu_find(edge[i].u);
        int root_v = dsu_find(edge[i].v);
        // 树上不会出现这种情形（保留边构成的子图永远无环），这里只是防御性判断
        if (root_u == root_v) continue;

        if (has_enemy[root_u] && has_enemy[root_v]) {
            // 两端连通块里都有敌城：保留这条边等于把两队敌军连起来，只能破坏
            answer += edge[i].w;
            continue;
        }

        // 至少有一端没有敌城：保留这条边是安全的，把两块合成一块
        int root = dsu_merge(root_u, root_v);
        has_enemy[root] = has_enemy[root_u] || has_enemy[root_v];
    }

    cout << answer << '\n';
    return 0;
}
