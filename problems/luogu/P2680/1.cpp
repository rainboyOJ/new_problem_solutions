/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-03
 */
#include <bits/stdc++.h>
using namespace std;

// P2680 N, M <= 300,000
const int maxn = 300005; 
const int maxe = 600005; // 双向边

int n, m;
int diff[maxn];   // 差分数组
int val[maxn];    // val[u] 表示 u 到 fa[u] 的边权
int dist[maxn];   // dist[u] 表示 u 到 root 的距离
int max_edge_on_limit_path; // 辅助变量

// 存储查询，避免二分时重复计算 LCA
struct Query {
    int u, v, lca, len;
} q[maxn];

// === 链式前向星 ===
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt;
    
    linkList(){ reset(); }
    void reset() { edge_cnt=0; memset(h,-1,sizeof(h)); }
    
    void add2(int u, int v, int w) {
        e[edge_cnt] = {u, v, w, h[u]}; h[u] = edge_cnt++;
        e[edge_cnt] = {v, u, w, h[v]}; h[v] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }

    // Iterator 语法糖 (为了节省篇幅，这里简化为只用 adj)
#ifdef __cpp_range_based_for
    struct AdjIterator {
        int i; linkList* p;
        AdjIterator(linkList* p, int i) : p(p), i(i) {}
        AdjIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const AdjIterator& oth) { return i != oth.i; }
        // 返回 pair<int, int> : {v, w}
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

// === LCA 模板 ===
const int MAXLOG = 20;   
struct LCA {
    int f[maxn][MAXLOG + 1];
    int d[maxn];

    void init(int n, int root){
        dfs(root, 0, 1, 0); 
        // 黑洞优化
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                f[i][j] = f[ f[i][j-1] ][ j-1 ];
            }
        }
    }

    // DFS: 顺便处理 dist 和 val
    void dfs(int u, int fa, int depth, int w_from_fa) {
        d[u] = depth;
        f[u][0] = fa; 
        val[u] = w_from_fa; // 记录边权
        
        for (auto [v, w] : e.adj(u)) { // 使用修改后的语法糖，拿到 w
            if (v != fa) {
                dist[v] = dist[u] + w;
                dfs(v, u, depth + 1, w);
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
} lca;

// === 核心 Check 函数 ===
// 检查是否能在 limit 时间内完成
// 统计 diff 的 DFS
// u 当前点 , fa 父节点
// cnt 不达标的边的数量
// max_path_len 最长的边的值
// limit 边长的上线
bool dfs_check(int u, int fa, int cnt, int max_path_len, int limit) {
    bool found = false;
    for(auto [v, w] : e.adj(u)) {
        if(v == fa) continue;
        if(dfs_check(v, u, cnt, max_path_len, limit)) found = true; // 只要子树找到了，就标记
        diff[u] += diff[v]; // 累加差分
    }
    
    // 如果已经找到了可行解，不需要继续判断当前点，但需要继续回溯累加diff
    if (found) return true;

    // 核心判断：
    // 1. diff[u] == cnt : 说明这条边 (u, fa) 被所有超标路径覆盖
    // 2. max_path_len - val[u] <= limit : 减去这条边后，最长的那条路径满足限制
    if (diff[u] == cnt && max_path_len - val[u] <= limit) {
        return true;
    }
    return false;
}

bool check(int limit) {
    memset(diff, 0, sizeof(int) * (n + 1));
    int cnt = 0;           // 超标路径数量
    int max_len = 0;       // 超标路径中的最大长度

    // 1. 找出所有超标路径，并进行差分
    for(int i = 1; i <= m; ++i) {
        if(q[i].len > limit) {
            cnt++;
            max_len = max(max_len, q[i].len);
            // 边差分：u++, v++, lca -= 2
            diff[q[i].u]++;
            diff[q[i].v]++;
            diff[q[i].lca] -= 2;
        }
    }

    // 如果没有超标路径，说明 limit 是可行的（不需要删边）
    if(cnt == 0) return true;

    // 2. DFS 统计差分并寻找符合条件的边
    // 从根节点 1 开始
    return dfs_check(1, 0, cnt, max_len, limit);
}

void init(){
    cin >> n >> m;
    for(int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.add2(u, v, w);
    }
    
    lca.init(n, 1);

    // 预处理所有查询
    for(int i = 1; i <= m; ++i) {
        cin >> q[i].u >> q[i].v;
        q[i].lca = lca.ask(q[i].u, q[i].v);

        //树上唯一路径的 长度
        q[i].len = dist[q[i].u] + dist[q[i].v] - 2 * dist[q[i].lca];
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    init();

    // 二分答案
    // 左边界 0，右边界为最长路径（或者所有边权和，这里取个大数就行，最长路径肯定<=边权和）
    int l = 0, r = 300000 * 1000; // 最坏情况
    // 优化右边界：取所有计划中的最大长度
    int max_q_len = 0;
    for(int i=1;i<=m;++i) max_q_len = max(max_q_len, q[i].len);
    r = max_q_len;

    int ans = max_q_len;

    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(mid)) {
            ans = mid;
            r = mid; // 尝试更小的时间
        } else {
            l = mid + 1; // 必须更长时间
        }
    }

    cout << ans << endl;
    
    return 0;
}
