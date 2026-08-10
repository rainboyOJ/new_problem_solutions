#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXK = 10;
const long long INF = (1LL << 62);

struct Edge {
    // 一条无向边：端点为 u、v，修建或修复费用为 w。
    int u;
    int v;
    long long w;

    // rbook 的 Kruskal 模板通过 operator< 按边权排序。
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

int n, m, k;
long long town_cost[MAXK];             // town_cost[j]：城市化第 j 个乡镇的固定费用
long long subset_cost[1 << MAXK];      // subset_cost[mask]：mask 中所有乡镇的固定费用和

vector<Edge> original_edges;           // 原有城市之间的全部 m 条边
vector<Edge> original_mst;             // 原图的一棵 MST，恰有 n-1 条边
vector<Edge> town_edges;               // 所有乡镇到原有城市的 n*k 条边

int fa[MAXN + MAXK];                   // 并查集父亲
int dsu_size[MAXN + MAXK];             // 并查集所在连通块的大小

// 每次 Kruskal 前，都要让每个节点重新成为一个独立连通块。
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

bool merge_set(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);
    if (root_u == root_v) {
        return false;
    }

    // 小树接到大树上，与路径压缩配合，保证并查集操作足够快。
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
            // 原有城市编号为 1..n，乡镇 town 的节点编号为 n+town+1。
            edge.v = n + town + 1;
            cin >> edge.w;
            town_edges.push_back(edge);
        }
    }
}

// 使用 rbook 的标准 Kruskal 思路，求出只含原有城市时的一棵 MST。
// 题解中的交换证明保证：以后无论选择哪些乡镇，其他原图边都可以删去。
void build_original_mst() {
    sort(original_edges.begin(), original_edges.end());
    init_dsu(n);

    for (int i = 0; i < (int)original_edges.size(); i++) {
        const Edge &edge = original_edges[i];
        // 两端已经连通，再选这条边就会形成环。
        if (!merge_set(edge.u, edge.v)) {
            continue;
        }

        original_mst.push_back(edge);
        if ((int)original_mst.size() == n - 1) {
            break;
        }
    }
}

// 用 lowbit 递推每个乡镇集合的固定费用。
void build_subset_cost() {
    subset_cost[0] = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        int lowbit = mask & -mask;
        int town = 0;
        while ((1 << town) != lowbit) {
            town++;
        }
        // 去掉最低位的乡镇，再加回这个乡镇的城市化费用。
        subset_cost[mask] = subset_cost[mask ^ lowbit] + town_cost[town];
    }
}

// 从乡镇节点编号还原乡镇下标，判断这条边能否出现在当前 mask 中。
bool town_edge_is_available(const Edge &edge, int mask) {
    int town = edge.v - n - 1;
    return (mask & (1 << town)) != 0;
}

// 在“原图 MST 边 + mask 允许的乡镇边”上执行 Kruskal。
long long solve_mask(int mask) {
    int selected_towns = __builtin_popcount((unsigned)mask);
    // 当前扩展图有 n+selected_towns 个有效节点，生成树需要“点数-1”条边。
    int need_edges = n + selected_towns - 1;
    int selected_edges = 0;
    long long answer = subset_cost[mask];

    // 数组统一初始化到 n+k；未被 mask 选择的乡镇节点始终不会参与合并。
    init_dsu(n + k);

    int original_pos = 0;
    int town_pos = 0;

    // original_mst 与 town_edges 都已按边权排序。
    // 用双指针取两个序列当前更小的边，就等价于把两组边合并后再跑 Kruskal。
    while (selected_edges < need_edges) {
        // 跳过属于未选乡镇的边，它们不在当前扩展图中。
        while (town_pos < (int)town_edges.size() &&
               !town_edge_is_available(town_edges[town_pos], mask)) {
            town_pos++;
        }

        // 比较两组序列的队首，决定 Kruskal 下一条检查哪条边。
        bool take_original = false;
        if (original_pos < (int)original_mst.size()) {
            if (town_pos == (int)town_edges.size() ||
                original_mst[original_pos].w <= town_edges[town_pos].w) {
                take_original = true;
            }
        }

        Edge edge;
        if (take_original) {
            edge = original_mst[original_pos];
            original_pos++;
        } else {
            if (town_pos == (int)town_edges.size()) {
                return INF;
            }
            edge = town_edges[town_pos];
            town_pos++;
        }

        // 只有连接两个不同连通块时才真正选择这条边。
        if (merge_set(edge.u, edge.v)) {
            answer += edge.w;
            selected_edges++;
        }
    }

    return answer;
}

void solve() {
    // 百万条原图边只处理一次，以后每个 mask 只扫描 n-1 条原图 MST 边。
    build_original_mst();
    sort(town_edges.begin(), town_edges.end());
    build_subset_cost();

    long long answer = INF;
    // k<=10，直接枚举哪些乡镇实际参与连通。
    for (int mask = 0; mask < (1 << k); mask++) {
        answer = min(answer, solve_mask(mask));
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
