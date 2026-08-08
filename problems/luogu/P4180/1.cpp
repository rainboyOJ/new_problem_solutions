/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-03 20:15:14
 * Modified for Strictly Second MST
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e5+5; // 题目范围 N<=10^5
const int maxe = 3e5+5; // M<=3*10^5
const ll INF64 = 1e18;  // 用于初始化次大值
const int INF = 2e9; 
int n, m;
ll mst_res;

// 边的结构体
struct Edge {
    int u, v;
    long long w;
    int id;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

// Kruskal 算法封装
struct KruskalAlgorithm {
    struct DSU {
        std::vector<int> fa;
        void init(int n) {
            fa.resize(n + 1);
            std::iota(fa.begin(), fa.end(), 0);
        }
        int find(int x) {
            return x == fa[x] ? x : fa[x] = find(fa[x]);
        }
        bool merge(int x, int y) {
            int fx = find(x), fy = find(y);
            if (fx == fy) return false;
            fa[fx] = fy;
            return true;
        }
    } dsu;

    int n;
    std::vector<Edge> edges;
    std::vector<bool> in_mst; // 标记边是否在 MST 中

    void init(int _n, int _m) {
        n = _n;
        edges.clear();
        dsu.init(n);
        in_mst.assign(_m + 1, false);
    }

    void add_edge(int u, int v, long long w, int id) {
        edges.push_back({u, v, w, id});
    }

    long long solve() {
        std::sort(edges.begin(), edges.end());
        dsu.init(n);
        long long ans = 0;
        int cnt = 0;
        for (const auto& e : edges) {
            if (dsu.merge(e.u, e.v)) {
                ans += e.w;
                cnt++;
                in_mst[e.id] = true; // 标记这条边是树边
            }
            if (cnt == n - 1) break;
        }
        if (cnt < n - 1) return -1;
        return ans;
    }
} kruskal;

// 链式前向星
struct linkList {
    struct edge { int u, v, w, next; };
    edge e[maxe * 2]; // 无向图双向边，大小要翻倍
    int h[maxn], edge_cnt;
    linkList() { edge_cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int u, int v, int w = 0) { 
        e[edge_cnt] = {u, v, w, h[u]}; h[u] = edge_cnt++; 
    }
    void add2(int u, int v, int w = 0) {
        add(u, v, w); add(v, u, w);
    }
    edge & operator[](int id) { return e[id]; }
} e;

const int MAXLOG = 18; // 2^18 > 100000

// 核心工具：合并两个区间的最值信息
// 返回 {最大值, 严格次大值}
pair<int, int> merge_info(pair<int, int> a, pair<int, int> b) {
    // 收集所有可能的候选值
    int c[4] = {a.first, a.second, b.first, b.second};
    int mx = -INF, se = -INF;
    
    // 找最大值
    for(int i=0; i<4; ++i) mx = max(mx, c[i]);
    
    // 找严格次大值 (必须严格小于 mx)
    for(int i=0; i<4; ++i) {
        if (c[i] < mx) {
            se = max(se, c[i]);
        }
    }
    return {mx, se};
}

struct LCA {
    int f[maxn][MAXLOG + 1];
    int mx[maxn][MAXLOG + 1]; // 区间最大值
    int se[maxn][MAXLOG + 1]; // 区间严格次大值
    int d[maxn];

    void init(int n, int root) {
        // 1. DFS 预处理深度、父亲和第一级边权
        dfs(root, 0, 1, -INF); // 根节点的父边权值设为 -INF

        // 2. 倍增预处理
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                f[i][j] = f[f[i][j - 1]][j - 1];
                
                // 关键：合并 [i, 2^(j-1)] 和 [2^(j-1), 2^j] 两段的信息
                pair<int, int> info = merge_info(
                    {mx[i][j-1], se[i][j-1]},
                    {mx[f[i][j-1]][j-1], se[f[i][j-1]][j-1]}
                );
                mx[i][j] = info.first;
                se[i][j] = info.second;
            }
        }
    }

    // DFS 增加 w_from_fa 参数：这是连接 u 和 fa 的边的权值
    void dfs(int u, int fa, int depth, int w_from_fa) {
        d[u] = depth;
        f[u][0] = fa;
        mx[u][0] = w_from_fa;
        se[u][0] = -INF; // 一条边没有次大值，初始化为无穷小
        
        for (int i = e.h[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            int w = e[i].w;
            if (v != fa) {
                dfs(v, u, depth + 1, w);
            }
        }
    }

    // 查询 u 到 v 路径上的 {最大值, 严格次大值}
    // 注意：这里不需要求 LCA 点本身，只需要路径上的边权信息
    pair<int, int> ask_path_info(int u, int v) {
        pair<int, int> res = {-INF, -INF};
        
        // 保证 u 是 深度深的那个
        if (d[u] < d[v]) swap(u, v);

        // 1. u 向上跳到和 v 同层
        for (int i = MAXLOG; i >= 0; --i) {
            if (d[u] - (1 << i) >= d[v]) {
                // 合并 u 跳跃过程中的最值
                res = merge_info(res, {mx[u][i], se[u][i]});
                u = f[u][i];
            }
        }

        if (u == v) return res;

        // 2. u 和 v 一起向上跳
        for (int i = MAXLOG; i >= 0; --i) {
            if (f[u][i] != f[v][i]) {
                res = merge_info(res, {mx[u][i], se[u][i]});
                res = merge_info(res, {mx[v][i], se[v][i]});
                u = f[u][i];
                v = f[v][i];
            }
        }

        // 3. 最后还要加上连接 LCA 的那两条边 (u->LCA, v->LCA)
        res = merge_info(res, {mx[u][0], se[u][0]});
        res = merge_info(res, {mx[v][0], se[v][0]});
        
        return res;
    }
} lca;

void init() {
    std::cin >> n >> m;
    kruskal.init(n, m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
        kruskal.add_edge(u, v, w, i);
    }
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    
    // 1. 求 MST
    mst_res = kruskal.solve();

    // 2. 构建 MST 图 (仅包含树边)
    // 你的 Kruskal 结构体里有一个 in_mst 数组，这很好
    for (const auto& ke : kruskal.edges) {
        if (kruskal.in_mst[ke.id]) {
            e.add2(ke.u, ke.v, ke.w); // 注意这里要把权值 ke.w 传进去！
        }
    }

    // 3. LCA 初始化 (倍增预处理最值)
    // 注意：数据可能不连通(虽然题目保证有解)，通常以 1 为根
    lca.init(n, 1);

    ll ans = INF64; // 严格次小生成树的权值

    // 4. 遍历所有 非树边
    for (const auto& ke : kruskal.edges) {
        if (!kruskal.in_mst[ke.id]) {
            int u = ke.u;
            int v = ke.v;
            ll w = ke.w;
            
            // 特判：如果是自环，忽略
            if (u == v) continue;

            // 查询树上路径 u -> v 的最大值和严格次大值
            pair<int, int> info = lca.ask_path_info(u, v);
            int max1 = info.first;
            int max2 = info.second;

            //  
            // 此时 u-v 这条非树边和树上路径构成了环
            // 我们要尝试用 w 替换掉环上的一条边
            
            if (w > max1) {
                // 如果非树边比路径最大边大，直接替换最大边
                ans = min(ans, mst_res - max1 + w);
            } else if (w == max1) {
                // 如果相等，说明替换最大边得不到"严格"次小
                // 必须退而求其次，替换严格次大边
                if (max2 != -INF) { // 确保存在次大边
                    ans = min(ans, mst_res - max2 + w);
                }
            }
            // 注意：w < max1 是不可能的，否则 T 就不是 MST 了
        }
    }
    
    // 输出结果
    cout << ans << endl;

    return 0;
}
