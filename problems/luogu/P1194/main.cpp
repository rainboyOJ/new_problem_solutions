/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 21:46
 * update_at: 2026-10-21 14:35
 */
// 买礼物：每件礼物可花 A 元直接买；若已买 i，则买 j 只需 K[i][j] 元。求买齐全部的最小花费。
// 建模：加虚拟源点 S（编号 B+1）表示"从商店原价买"，于是
//   S -- j       权 A          直接买第 j 件
//   i -- j       权 K[i][j]    已买 i 后，用优惠价买 j
// 买齐全部 = 让 S 和所有礼物点连通，总花费 = 选中边的权和，所以是最小生成树。
// 最优解一定无环：有环就删掉环上任一条，连通性不变、代价不增，于是连通且无环即为树。
// 反向也成立：树连通，从 S 做 BFS 能到达所有礼物，按 BFS 序购买时父节点必已买好。
// 注意 K[i][j] = 0 表示"没有优惠"，必须当无边跳过，不能当 0 权边（否则会误以为能免费连锁）。
// 这里用 Kruskal：边数约 B^2/2 + B，B <= 500 时最多约 12.5 万条，按边权排序后扫描即可。
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// 一条无向边：从 u 连到 v，边权 w。点编号 1..n，n >= 1。
// 点编号要当数组下标用，写成 int；边权和可能很大，用 ll。
struct Edge {
    int u;  // 起点
    int v;  // 终点
    ll w;   // 边权
};

// 边权小的排在前面，Kruskal 每次都先试当前最小的边。
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

// 找 x 所在集合的根，顺路把路径上的点直接挂到根上（路径压缩）。
int dsu_find(vector<int> &dsu_parent, int x) {
    if (dsu_parent[x] == x) return x;
    dsu_parent[x] = dsu_find(dsu_parent, dsu_parent[x]);
    return dsu_parent[x];
}

// 合并 a、b 所在的两个集合；两端本来就连通时返回 false。
// dsu_size[x] 是 x 当根时该集合的点数，用来按大小合并。
bool dsu_merge(vector<int> &dsu_parent, vector<int> &dsu_size, int a, int b) {
    int root_a = dsu_find(dsu_parent, a);
    int root_b = dsu_find(dsu_parent, b);
    if (root_a == root_b) return false;
    // 小集合接到大集合下面，配合路径压缩，单次操作接近常数。
    if (dsu_size[root_a] < dsu_size[root_b]) swap(root_a, root_b);
    dsu_parent[root_b] = root_a;
    dsu_size[root_a] += dsu_size[root_b];
    return true;
}

// 求最小生成树，按值接收边表，排序不会打乱调用者的边表顺序。
// 返回 true：图连通，answer 存 MST 的总权值；
// 返回 false：图不连通，没有生成树，answer 无意义。
bool kruskal(int n, vector<Edge> edges, ll &answer) {
    sort(edges.begin(), edges.end(), cmp_edge);

    // 并查集要跟着 n 开，放在函数里比固定大小的全局数组安全。
    vector<int> dsu_parent(n + 1);   // dsu_parent[x]：x 的父节点，x 是根时等于 x
    vector<int> dsu_size(n + 1, 1);  // dsu_size[x]：x 是根时集合的大小
    for (int i = 1; i <= n; i++) dsu_parent[i] = i;

    answer = 0;
    int selected = 0;  // 已选边数，一棵生成树正好要 n - 1 条

    for (const Edge &edge : edges) {
        // 自环、两端已经连通的边都会成环，不能选。
        if (!dsu_merge(dsu_parent, dsu_size, edge.u, edge.v)) continue;
        answer += edge.w;
        selected++;
        if (selected == n - 1) break;
    }

    return selected == n - 1;  // 单点图选 0 条边：连通，答案为 0
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int direct_cost;  // 直接买任意一件礼物的价格 A
    int gift_cnt;     // 礼物数量 B
    cin >> direct_cost >> gift_cnt;

    int source = gift_cnt + 1;  // 虚拟源点 S，表示"从商店原价买"
    vector<Edge> edges;
    edges.reserve(gift_cnt * gift_cnt);  // 优惠边最坏 B*(B-1)/2 条，加 B 条源点边

    // S 到每件礼物：权 A，表示直接买
    for (int j = 1; j <= gift_cnt; j++) {
        edges.push_back({source, j, direct_cost});
    }

    // 礼物之间的优惠边：只取上三角，矩阵对称不必重复建
    for (int i = 1; i <= gift_cnt; i++) {
        for (int j = 1; j <= gift_cnt; j++) {
            int price;
            cin >> price;
            if (i >= j) continue;      // 对角线 K[i][i]=0 与下三角都跳过
            if (price == 0) continue;  // 0 表示没有优惠，当无边处理
            edges.push_back({i, j, price});
        }
    }

    ll answer = 0;
    // 所有礼物都有一条到 S 的边，所以这张图必然连通，返回值一定为 true
    kruskal(source, edges, answer);
    cout << answer << '\n';

    return 0;
}
