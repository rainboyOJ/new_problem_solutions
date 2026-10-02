/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 23:04
 * update_at: 2026-10-01 23:04
 */
// main.cpp：先求原图 MST（百万条边只处理一次），再枚举乡镇子集，
// 在“MST 边 + 选中乡镇的连边”上跑 Kruskal 求最小生成树。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10005;   // n <= 1e4
const int MAXK = 11;      // k <= 10
const ll INF = 1LL << 62;

// 一条无向边：端点 u、v，修建或修复费用 w。
struct Edge {
    int u;
    int v;
    ll w;
};

// 按边权升序，Kruskal 需要。
bool cmp_edge(const Edge &x, const Edge &y) {
    return x.w < y.w;
}

int n, m, k;
ll town_cost[MAXK];         // town_cost[j]：把第 j 个乡镇城市化的固定费用
ll subset_cost[1 << MAXK];  // subset_cost[mask]：mask 中全部乡镇的城市化费用和

vector<Edge> original_edges; // 原有城市之间的全部 m 条边
vector<Edge> original_mst;   // 原图的一棵 MST，恰好 n-1 条边
vector<Edge> town_edges;     // 乡镇到原有城市的 n*k 条边

int fa[MAXN + MAXK];        // 并查集父亲
int dsu_size[MAXN + MAXK];  // 并查集连通块大小，用于按大小合并

// 每次 Kruskal 前把每个结点恢复成独立集合。
void init_dsu(int node_count) {
    for (int i = 1; i <= node_count; i++) {
        fa[i] = i;
        dsu_size[i] = 1;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = find_root(fa[x]);
}

// 合并两个连通块，返回是否真的发生了合并。
bool merge_set(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);
    if (root_u == root_v) {
        return false;
    }

    // 小树挂到大树上，与路径压缩配合，单次操作近乎常数。
    if (dsu_size[root_u] < dsu_size[root_v]) {
        swap(root_u, root_v);
    }
    fa[root_v] = root_u;
    dsu_size[root_u] += dsu_size[root_v];
    return true;
}

void read_input() {
    cin >> n >> m >> k;

    original_edges.reserve(m);
    town_edges.reserve(n * k);

    for (int i = 1; i <= m; i++) {
        Edge edge;
        cin >> edge.u >> edge.v >> edge.w;
        original_edges.push_back(edge);
    }

    for (int town = 0; town < k; town++) {
        cin >> town_cost[town];
        for (int city = 1; city <= n; city++) {
            Edge edge;
            edge.u = city;
            edge.v = n + town + 1;   // 乡镇 town 的结点编号是 n+town+1
            cin >> edge.w;
            town_edges.push_back(edge);
        }
    }
}

// 求只含原有城市时的一棵 MST。
// 交换论证保证：无论选了哪些乡镇，其他原图边都不必再看。
void build_original_mst() {
    sort(original_edges.begin(), original_edges.end(), cmp_edge);
    init_dsu(n);

    int cnt = original_edges.size();
    int mst_cnt = 0;
    for (int i = 0; i < cnt; i++) {
        const Edge &edge = original_edges[i];
        if (!merge_set(edge.u, edge.v)) {
            continue;   // 两端已连通，选它就会成环
        }

        original_mst.push_back(edge);
        mst_cnt++;
        if (mst_cnt == n - 1) {
            break;
        }
    }
}

// 用 lowbit 递推出每个乡镇子集的固定费用。
void build_subset_cost() {
    subset_cost[0] = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        ll sum = 0;
        for (int town = 0; town < k; town++) {
            if (mask & (1 << town)) {
                sum += town_cost[town];
            }
        }
        subset_cost[mask] = sum;
    }
}

// 这条乡镇边的另一端是否属于 mask 中被选中的乡镇。
bool town_edge_is_available(const Edge &edge, int mask) {
    int town = edge.v - n - 1;
    return (mask & (1 << town)) != 0;
}

// 在“原图 MST 边 + mask 允许的乡镇边”上跑一次 Kruskal。
ll solve_mask(int mask) {
    int selected_towns = __builtin_popcount(mask);
    // 扩展图有 n + selected_towns 个结点，生成树需要结点数减一条边。
    int need_edges = n + selected_towns - 1;
    int selected_edges = 0;
    ll answer = subset_cost[mask];

    // 并查集统一开到 n+k；未被 mask 选中的乡镇结点不会参与任何合并。
    init_dsu(n + k);

    // original_mst 与 town_edges 都已按边权排序，
    // 双指针取两边当前更小的边，就等价于把两组边归并后再跑 Kruskal。
    int original_pos = 0;
    int town_pos = 0;
    int town_total = town_edges.size();

    while (selected_edges < need_edges) {
        // 先跳过不属于选中乡镇的边，它们不在当前扩展图里。
        while (town_pos < town_total && !town_edge_is_available(town_edges[town_pos], mask)) {
            town_pos++;
        }

        bool take_original = false;
        if (original_pos < n - 1) {
            if (town_pos == town_total || original_mst[original_pos].w <= town_edges[town_pos].w) {
                take_original = true;
            }
        }

        Edge edge;
        if (take_original) {
            edge = original_mst[original_pos];
            original_pos++;
        } else {
            if (town_pos == town_total) {
                return INF;   // 边用尽仍没连通，实际不会发生
            }
            edge = town_edges[town_pos];
            town_pos++;
        }

        // 只有连通两个不同连通块时才真正选中这条边。
        if (merge_set(edge.u, edge.v)) {
            answer += edge.w;
            selected_edges++;
        }
    }

    return answer;
}

void solve() {
    // 百万条原图边只处理一次，之后每个 mask 只扫 n-1 条 MST 边。
    build_original_mst();
    sort(town_edges.begin(), town_edges.end(), cmp_edge);
    build_subset_cost();

    // k <= 10，直接枚举实际参与连通的乡镇集合。
    ll answer = INF;
    for (int mask = 0; mask < (1 << k); mask++) {
        ll current = solve_mask(mask);
        if (current < answer) {
            answer = current;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
