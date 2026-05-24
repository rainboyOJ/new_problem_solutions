/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-04 15:40:22
 * Problem: Forest Shortest Path (LCA on Forest)
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 10005;   // N <= 10000
const int maxe = 20005;   // M < 10000, 双向边需要 x2

int n, m, c;

// === 1. 链式前向星 ===
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt;
    
    linkList(){ reset(); }
    
    // 多组数据，务必重置
    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }
    
    void add2(int u, int v, int w) {
        e[edge_cnt] = {u, v, w, h[u]}; h[u] = edge_cnt++;
        e[edge_cnt] = {v, u, w, h[v]}; h[v] = edge_cnt++;
    }

    // 语法糖
#ifdef __cpp_range_based_for
    struct AdjIterator {
        int i; linkList* p;
        AdjIterator(linkList* p, int i) : p(p), i(i) {}
        AdjIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const AdjIterator& oth) { return i != oth.i; }
        pair<int, int> operator*() { return {p->e[i].v, p->e[i].w}; }
    };
    struct BaseRange {
        int start; linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        AdjIterator begin() { return AdjIterator(p, p->h[start]); }
        AdjIterator end()   { return AdjIterator(p, -1); }
    };
    BaseRange adj(int u) { return BaseRange(this, u); }
#endif
} e;

// === 2. LCA 模板 (支持森林 + 连通性检查) ===
const int MAXLOG = 15; // 2^14 > 10000 足够了
struct LCA {
    int f[maxn][MAXLOG + 1];
    int d[maxn];      // 深度
    int dis[maxn];    // 距离根的带权距离
    int belong[maxn]; // 记录点 u 属于哪棵树(存储根节点编号)

    // 初始化：处理森林
    void init(int n) {
        // 多组数据，d数组必须清零，作为visited标记使用
        memset(d, 0, sizeof(d)); 
        // f数组也清零比较安全
        memset(f, 0, sizeof(f));
        
        // 遍历所有点，处理森林中的每一棵树
        for(int i = 1; i <= n; ++i) {
            if(!d[i]) { // 如果深度为0，说明还没访问过，是一个新的连通块
                // 根节点的 belong 设为它自己，深度设为1，距离设为0
                dfs(i, 0, 1, 0, i);
            }
        }
        
        // 倍增预处理
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                f[i][j] = f[ f[i][j-1] ][ j-1 ];
            }
        }
    }

    // DFS: 增加 root_id 参数，标记连通分量
    void dfs(int u, int fa, int depth, int current_dist, int root_id) {
        d[u] = depth;
        f[u][0] = fa; 
        dis[u] = current_dist;
        belong[u] = root_id; // 标记阵营
        
        for (auto [v, w] : e.adj(u)) { 
            if (v != fa) {
                dfs(v, u, depth + 1, current_dist + w, root_id);
            }
        }
    }

    int ask_lca(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        for (int i = MAXLOG; i >= 0; --i) {
            if (d[u] - (1 << i) >= d[v]) u = f[u][i];
        }
        if (u == v) return u;
        for (int i = MAXLOG; i >= 0; --i) {
            if (f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    }
    
    // 查询接口
    void query(int u, int v) {
        // 1. 连通性判断
        if (belong[u] != belong[v]) {
            cout << "Not connected\n";
            return;
        }
        
        // 2. 距离计算
        int l = ask_lca(u, v);
        int ans = dis[u] + dis[v] - 2 * dis[l];
        cout << ans << "\n";
    }

} lca;

int main() {
    // 必须优化IO，C 很大
    ios::sync_with_stdio(false); cin.tie(0);
    
    // 处理多组输入
    while(cin >> n >> m >> c) {
        e.reset(); // 清空边
        
        for(int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            e.add2(u, v, w);
        }
        
        // 初始化 LCA (内部处理森林)
        lca.init(n);
        
        for(int i = 0; i < c; ++i) {
            int u, v;
            cin >> u >> v;
            lca.query(u, v);
        }
    }
    
    return 0;
}
