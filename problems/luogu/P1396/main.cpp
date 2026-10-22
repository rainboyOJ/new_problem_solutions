/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 16:59
 * update_at: 2026-10-21 17:30
 */
// 营救：求 s 到 t 的所有路径中，「路径上最大边权」的最小值，即瓶颈路。
// 本文件用 Kruskal + 并查集：按边权升序加边，边 (u,v) 一旦让 s 与 t 首次连通，
// 这条边的权值就是答案。
//
// 为什么对：Kruskal 处理完所有权 <= L 的边后，并查集的连通块恰好等于
// 「只走权 <= L 的边时图的分量」。于是
//   s、t 在只走权 <= L 的边时连通  <=>  Kruskal 加完权 <= L 的边后 s、t 已同块
// 而答案正是让 s、t 连通的最小阈值 L，所以「首次连通时那条边的权」就是 L。
// 这条性质只依赖边权的处理顺序，与同权边谁先谁后无关，所以任意一棵 MST 都对。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10000 + 5;  // 区数上界 n <= 1e4
const int MAXM = 20000 + 5;  // 大道数上界 m <= 2e4

// 一条无向边：从 u 连到 v，拥挤度 w。点编号 1..n。
struct Edge {
    int u;  // 起点
    int v;  // 终点
    ll w;   // 拥挤度
};

int n, m, start_node, target_node;
Edge edges[MAXM];
int dsu_parent[MAXN];  // dsu_parent[x]：x 的父节点，x 是根时等于 x

// 边权小的排在前面，Kruskal 每次都先试当前最小的边。
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

// 找 x 所在集合的根，顺路把路径上的点直接挂到根上（路径压缩）。
int dsu_find(int x) {
    if (dsu_parent[x] == x) return x;
    dsu_parent[x] = dsu_find(dsu_parent[x]);
    return dsu_parent[x];
}

// 合并 a、b 所在的两个集合。
// 只靠路径压缩：单次操作摊还 O(log n)，本题 n <= 1e4 已经足够，
// 所以不再额外维护集合大小做按大小合并。
void dsu_merge(int a, int b) {
    dsu_parent[dsu_find(a)] = dsu_find(b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> start_node >> target_node;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // s == t 时不用走任何路，拥挤度上界是 0，必须先特判：
    // 否则并查集一开始就「已连通」，会错误地输出第一条边的权值。
    if (start_node == target_node) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        dsu_parent[i] = i;
    }

    sort(edges, edges + m, cmp_edge);

    for (int i = 0; i < m; i++) {
        dsu_merge(edges[i].u, edges[i].v);
        // 加入这条边后 s 与 t 首次连通，它的权就是最小瓶颈值。
        if (dsu_find(start_node) == dsu_find(target_node)) {
            cout << edges[i].w << '\n';
            return 0;
        }
    }

    // 题面保证 s 一定能到达 t，走不到这里
    cout << 0 << '\n';
    return 0;
}
