/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 10:20
 * update_at: 2026-10-21 10:20
 */
// P1550 [USACO08OCT] Watering Hole G
// 题意：第 i 块田可以花 W_i 打井，也可以花 P_ij 与第 j 块田铺一根水管；
//       求让所有田都有水（自己打井，或沿水管连到有水的田）的最小总花费。
//
// 建模：加一个虚拟水源点 S（编号 n + 1），表示"农场外面的那处水"。
//   S -- i   权 W_i    在第 i 块田打井，就是从这个水源接到第 i 块田
//   i -- j   权 P_ij   在两块田之间铺一根水管
// 这样"打井"和"铺管"都变成了同一种东西——一条边，于是
//   合法方案  <=>  S 与全部田连通的一张子图  <=>  一棵生成树
// 总花费就是选中边的权值和，问题变成在这个 n + 1 点图上求最小生成树。
//
// 注意 P_ij = 0 在本题是"免费水管"，是合法的 0 权边，必须建进图里；
// 只有 i == j 的对角线自环要跳过。
//
// 边数约 n^2/2 + n，n <= 300 时约 4.5 万条，用 Kruskal 排序后扫描即可。
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 305;              // 田地数上限 n <= 300
ll well_cost[MAXN];                // well_cost[i]：在第 i 块田打一口井的花费 W_i
ll pipe_cost[MAXN][MAXN];          // pipe_cost[i][j]：第 i 块田与第 j 块田之间铺水管的花费 P_ij

// 一条无向边：从 u 连到 v，边权 w。点编号 1..n+1（n+1 是虚拟水源点 S）。
// 点编号要当数组下标用，写成 int；边权和最大约 3e7，但统一用 ll 更稳。
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
bool kruskal(int node_cnt, vector<Edge> edges, ll &answer) {
    sort(edges.begin(), edges.end(), cmp_edge);

    // 并查集跟着点数开，放在函数里比固定大小的全局数组安全。
    vector<int> dsu_parent(node_cnt + 1);   // dsu_parent[x]：x 的父节点，x 是根时等于 x
    vector<int> dsu_size(node_cnt + 1, 1);  // dsu_size[x]：x 是根时该集合的点数
    for (int i = 1; i <= node_cnt; i++) dsu_parent[i] = i;

    answer = 0;
    int selected = 0;  // 已选边数，一棵生成树正好要 node_cnt - 1 条

    for (const Edge &edge : edges) {
        // 自环、两端已经连通的边都会成环，不能选。
        if (!dsu_merge(dsu_parent, dsu_size, edge.u, edge.v)) continue;
        answer += edge.w;
        selected++;
        if (selected == node_cnt - 1) break;
    }

    return selected == node_cnt - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int field_cnt;  // 田地数 n
    cin >> field_cnt;

    // 打井代价：每块田从水源接一条边
    for (int i = 1; i <= field_cnt; i++) {
        cin >> well_cost[i];
    }
    // 铺管代价矩阵
    for (int i = 1; i <= field_cnt; i++) {
        for (int j = 1; j <= field_cnt; j++) {
            cin >> pipe_cost[i][j];
        }
    }

    int source = field_cnt + 1;  // 虚拟水源点 S，表示"农场外面的那处水"
    vector<Edge> edges;
    edges.reserve(field_cnt * field_cnt + field_cnt);

    // S 到每块田：权 W_i，表示"在这块田打井"
    for (int i = 1; i <= field_cnt; i++) {
        edges.push_back({source, i, well_cost[i]});
    }

    // 田与田之间：只取上三角，矩阵对称不必重复建边
    for (int i = 1; i <= field_cnt; i++) {
        for (int j = 1; j <= field_cnt; j++) {
            if (i >= j) continue;  // 跳过对角线自环与下三角
            // P_ij = 0 是"免费水管"，是合法的 0 权边，绝不能像"无优惠"那样丢掉
            edges.push_back({i, j, pipe_cost[i][j]});
        }
    }

    ll answer = 0;
    // 每块田都有一条到 S 的边，这张图必然连通，返回值一定为 true
    kruskal(source, edges, answer);
    cout << answer << '\n';

    return 0;
}
