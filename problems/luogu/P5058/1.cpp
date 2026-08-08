/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-30 10:58:07
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m;
int a[maxn];
int st,ed;
int ans = 1e9; //存最小的点


//oisnip_begin code/graph/linklist.cpp 内容开始

// const int maxn = 1e6+5;
// const int maxe = 1e6+5;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
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
    // https://en.cppreference.com/w/cpp/language/range-for.html
#ifdef __cpp_range_based_for
    // C++ 模板 和 策略模式（Policy） 来消除重复代码。
    // 我们可以定义一个通用的迭代器模板，通过传入不同的“提取器（Getter）”来决定 operator* 返回什么。
    // === 1. 定义数据提取策略 (核心区别) ===
    
    // 策略A: 获取整条边 (对应原本的 Iterator)
    struct UseEdge {
        using ReturnType = edge&; // 定义返回类型
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };

    // 策略B: 只获取邻接点v (对应原本的 AdjIterator)
    struct UseAdj {
        using ReturnType = int;   // 定义返回类型
        static ReturnType get(linkList* p, int i) { return p->e[i].v; }
    };

    // === 2. 通用迭代器模板 (复用逻辑) ===
    template<typename Getter>
    struct BaseIterator {
        int i;          // 边的编号
        linkList* p;    // linkList指针
        
        BaseIterator(linkList* p, int i) : p(p), i(i) {}

        // 通用的遍历逻辑
        BaseIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const BaseIterator& oth) { return i != oth.i; }
        
        // 差异化逻辑：委托给 Getter 处理
        typename Getter::ReturnType operator*() { return Getter::get(p, i); }
    };

    // 定义具体的迭代器别名
    using Iterator    = BaseIterator<UseEdge>;
    using AdjIterator = BaseIterator<UseAdj>;

    // === 3. 通用范围类模板 ===
    template<typename IterT>
    struct BaseRange {
        int start;
        linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        IterT begin() { return IterT(p, p->h[start]); }
        IterT end()   { return IterT(p, -1); }
    };

    // === 4. 接口语法糖 ===
    
    // usage: for(auto& e : list(u))
    BaseRange<Iterator> operator()(int u) { return BaseRange<Iterator>(this, u); }

    // usage: for(int v : list.adj(u))
    BaseRange<AdjIterator> adj(int u) { return BaseRange<AdjIterator>(this, u); }
    
#endif
} e;

//oisnip_end code/graph/linklist.cpp 内容结束

//oisnip_begincut_node.cpp
struct TarjanCut {
    int n, timer; // timer 对应你代码中的 cnt
    int dfn[maxn], low[maxn];
    bool is_cut[maxn]; // 标记是否为割点 (对应 cut[])
    int root; // 当前 DFS 树的根节点

    void set(int _n) {
        n = _n;
        timer = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(is_cut, 0, sizeof(is_cut));
    }

    /*
     * u: 当前节点
     * fa: u 的父节点 (防止走回头路)
     */
    void dfs(int u, int fa = -1) {
        dfn[u] = low[u] = ++timer;
        int child = 0; // 记录 root 在 DFS 树中的子节点数量

        // for (int i = e(u); ~i; i = e[i].next) {
        for(auto v  : e.adj(u)){
            // int v = e[i].v;

            // 不走父子边
            if (v == fa) continue;

            // v 没有被访问过，是树边
            if (!dfn[v]) { 
                child++;
                dfs(v, u); // 【注意】这里必须传 u，表示 v 的父亲是 u

                // 回溯时用子节点的 low 更新当前节点的 low
                low[u] = std::min(low[u], low[v]);

                // 割点判定情况 2: 非根节点
                // 如果子节点 v 无法回到 u 的祖先 (low[v] >= dfn[u])
                // 说明 u 是连接 v 子树和其他部分的必经点

                // dfn[ed] >= dfn[v] 则 ed 在v的子树上
                if (low[v] >= dfn[u] && u != st && dfn[ed] >= dfn[v]) {
                    // is_cut[u] = true;
                    if( ans > u) ans = u;
                }

                // 处理返祖边
                // 注意:v可能是u的父亲,但没有关系,最多low[u] == dfn[fa[u]]
                // dfn[v] < dfn[u] 说明v是u的祖先,
                // 在无向图上其实不可能 dfn[v] > dfn[u]
                // 因为: v 是一个已经访问过的点, 如果dfn[v] > dfn[u] 说明u是v的祖先, 那么v在u的子树上,
                // 根据dfs 的性质, 应该先访问u, 再访问v,但此时v已经被访问, 所以不可能出现dfn[v] > dfn[u]的情况
            } else if( dfn[v] < dfn[u] ) {
                // v 已经被访问过，是返祖边 (Back Edge)
                // 用 v 的 dfn 更新 u 的 low
                low[u] = std::min(low[u], dfn[v]);
                // 注意：有些版本写成 min(low[u], low[v]) (对于已访问的 v) 是错误的。
                // 对于返祖边，只能取 dfn[v]，因为 low[v] 可能包含从 v 回到更上层的路径，
                // 而边 (u, v) 并不代表 u 可以通过 v 再跳跃回去（除非有其他边）。
            }
        }

        // 割点判定情况 1: 根节点
        // 如果根节点在 DFS 树中有两个及以上的子节点，则它是割点
        // if (u == root && child > 1) {
        //     is_cut[u] = true;
        // }
    }

    void solve() {
        // 遍历所有点，防止图不连通
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                root = i; // 记录当前连通块的 DFS 根
                dfs(i, 0); 
            }
        }
    }
    
    // 辅助函数：获取所有割点
    std::vector<int> get_cuts() {
        std::vector<int> cuts;
        for (int i = 1; i <= n; i++) {
            if (is_cut[i]) cuts.push_back(i);
        }
        return cuts;
    }
};
//oisnip_end
TarjanCut tj;

void init(){
    std::cin >> n;
    while (1) {
        int u,v;
        std::cin >> u >> v;
        if( u == 0 && v == 0) break;
        e.add2(u, v);
    }
    std::cin >> st >> ed;

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    tj.set(n);
    // tj.solve();
    tj.dfs(st);
    if (ans == 1e9) {
        std::cout << "No solution\n";
    } else {
        std::cout << ans << "\n";
    }
    
    return 0;
}
