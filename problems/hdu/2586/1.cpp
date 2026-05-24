/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-04 15:33:19
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 40005; 
const int maxe = 80005; // 双向边，容量翻倍

int n, m;

// === 1. 链式前向星模板 ===
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt;
    
    linkList(){ reset(); }
    
    // 多组数据必须重置
    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }
    
    void add2(int u, int v, int w) {
        e[edge_cnt] = {u, v, w, h[u]}; h[u] = edge_cnt++;
        e[edge_cnt] = {v, u, w, h[v]}; h[v] = edge_cnt++;
    }

    // 语法糖适配
#ifdef __cpp_range_based_for
    struct AdjIterator {
        int i; linkList* p;
        AdjIterator(linkList* p, int i) : p(p), i(i) {}
        AdjIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const AdjIterator& oth) { return i != oth.i; }
        // 返回 {v, w}
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

// === 2. LCA 模板 (支持距离查询) ===
const int MAXLOG = 20;   
struct LCA {
    int f[maxn][MAXLOG + 1];
    int d[maxn];      // 深度 (跳跃步数)
    int dis[maxn];    // **距离 (带权距离)**，用于求答案

    void init(int n, int root){
        // 从根节点开始，初始距离为 0
        dfs(root, 0, 1, 0); 
        
        // 倍增预处理
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                f[i][j] = f[ f[i][j-1] ][ j-1 ];
            }
        }
    }

    // DFS: 维护深度 d 和 带权距离 dis
    void dfs(int u, int fa, int depth, int current_dist) {
        d[u] = depth;
        f[u][0] = fa; 
        dis[u] = current_dist; // 记录该点到根的带权距离
        
        for (auto [v, w] : e.adj(u)) { 
            if (v != fa) {
                dfs(v, u, depth + 1, current_dist + w);
            }
        }
    }

    int ask(int u, int v) {
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
    
    // 新增：直接计算两点距离
    int get_dist(int u, int v) {
        int l = ask(u, v);
        return dis[u] + dis[v] - 2 * dis[l];
    }

} lca;

void solve() {
    // 多组数据，记得重置 linkList
    // LCA 的数组会被 init 覆盖，无需显式 memset，但图必须清空
    e.reset(); 
    
    cin >> n >> m;
    for(int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.add2(u, v, w);
    }
    
    lca.init(n, 1);
    
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        cout << lca.get_dist(u, v) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
        // 题目要求：每个测试用例结束后输出一个空行
        // (通常最后一个用例后是否需要看OJ判定，这里按照题目字面意思加)
        // 很多老题目POJ/UVa风格需要这个
        if (t >= 0) cout << "\n";
    }
    
    return 0;
}
