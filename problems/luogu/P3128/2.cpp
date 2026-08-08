/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-03 21:14:03
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

// P3128 N <= 50000，为了防止 MLE (f数组过大)，调整大小
const int maxn = 50005; 
const int maxe = 100005; // 双向边
const int mod = 1e9+7;

int n, m; // m 对应题目中的 K
int diff[maxn]; // 差分数组
int ans_val = 0; // 最终答案

//oisnip_begin code/graph/linklist.cpp 内容开始

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](int i){ return e[i]; }

    // 参考 语法糖
#ifdef __cpp_range_based_for
    struct UseEdge {
        using ReturnType = edge&; 
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };

    struct UseAdj {
        using ReturnType = int;   
        static ReturnType get(linkList* p, int i) { return p->e[i].v; }
    };

    template<typename Getter>
    struct BaseIterator {
        int i;          
        linkList* p;    
        
        BaseIterator(linkList* p, int i) : p(p), i(i) {}

        BaseIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const BaseIterator& oth) { return i != oth.i; }
        
        typename Getter::ReturnType operator*() { return Getter::get(p, i); }
    };

    using Iterator    = BaseIterator<UseEdge>;
    using AdjIterator = BaseIterator<UseAdj>;

    template<typename IterT>
    struct BaseRange {
        int start;
        linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        IterT begin() { return IterT(p, p->h[start]); }
        IterT end()   { return IterT(p, -1); }
    };

    BaseRange<Iterator> operator()(int u) { return BaseRange<Iterator>(this, u); }
    BaseRange<AdjIterator> adj(int u) { return BaseRange<AdjIterator>(this, u); }
    
#endif
} e;
//oisnip_end code/graph/linklist.cpp 内容结束

// === LCA 模板 (黑洞优化版) ===
const int MAXLOG = 20;   
struct LCA {
    int f[maxn][MAXLOG + 1];
    int d[maxn];

    // 初始化
    void init(int n, int root){
        dfs(root, 0, 1);
        
        // 倍增预处理：利用 f 全局初始化为 0 的特性 (黑洞)
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                f[i][j] = f[ f[i][j-1] ][ j-1 ];
            }
        }
    }

    // DFS 建树 - 使用了 linkList 的 range-based for 语法糖
    void dfs(int u, int fa, int depth) {
        d[u] = depth;
        f[u][0] = fa; 
        
        // 你的语法糖: for(int v : e.adj(u))
        for (int v : e.adj(u)) {
            if (v != fa) 
                dfs(v, u, depth + 1);
        }
    }

    // 查询 LCA
    int ask(int u, int v) {
        if (d[u] < d[v]) swap(u, v);

        for (int i = MAXLOG; i >= 0; --i) {
            if (d[u] - (1 << i) >= d[v]) {
                u = f[u][i];
            }
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

// === 统计答案 DFS ===
void dfs_calc(int u, int fa) {
    // 你的语法糖: for(int v : e.adj(u))
    for (int v : e.adj(u)) {
        if (v == fa) continue;
        dfs_calc(v, u);
        // 回溯时累加子树的差分值
        diff[u] += diff[v];
    }
    // 更新全局最大值
    ans_val = max(ans_val, diff[u]);
}

void init(){
    cin >> n >> m; // m 即题目中的 K
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        e.add2(u, v);
    }
    
    // 1. 初始化 LCA
    lca.init(n, 1);
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    init();

    // 2. 处理 K 条路径
    for(int i = 1; i <= m; ++i) {
        int s, t;
        cin >> s >> t;
        int l = lca.ask(s, t);
        int fa_l = lca.f[l][0];

        // 树上点差分公式
        diff[s]++;
        diff[t]++;
        diff[l]--;
        diff[fa_l]--; // 如果 l 是根，fa_l 为 0，diff[0]-- 安全
    }

    // 3. 统计答案
    dfs_calc(1, 0);

    cout << ans_val << endl;
    
    return 0;
}
