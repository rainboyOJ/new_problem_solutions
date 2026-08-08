/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-03 20:47:59
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m,root;
int a[maxn];


//oisnip_begin code/graph/linklist.cpp 内容开始

// const int maxn = 1e6+5;
// const int maxe = 1e6+5;

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

const int MAXLOG = 20;   
struct LCA {
    // f[u][i] 表示 u 的 2^i 祖先
    // d[u] 表示 u 的深度
    int f[maxn][MAXLOG + 1];
    int d[maxn];
    
    // 邻接表引用，避免全局依赖，初始化时传入
    // linklist *e;

    // 初始化函数
    // n: 节点数量
    // root: 根节点
    // void init(int n, int root,linlist & E);
        // *e = &E;
    void init(int n, int root){
        
        // 预处理深度和父节点
        dfs(root, 0, 1);
        
        // 倍增预处理：类似DP
        // f[u][j] = f[ f[u][j-1] ][ j-1 ]
        // 意思：u跳2^j步 = u先跳2^(j-1)步，再从那里跳2^(j-1)步
        for (int j = 1; j <= MAXLOG; ++j) {
            for (int i = 1; i <= n; ++i) {
                
                // 不需要判断中间点是否存在,如果中间的点不存在
                // 那么f[i][j] = 0 变成黑洞点
                f[i][j] = f[ f[i][j-1] ][ j-1 ];
              
            }
        }
    }

    // DFS 建树
    void dfs(int u, int fa, int depth) {
        d[u] = depth;
        f[u][0] = fa; // 2^0 = 1，直接父亲
        
        for (int i = e.h[u]; i!= -1;i = e[i].next) 
            if (e[i].v != fa) 
                dfs(e[i].v, u, depth + 1);

    }

    // 查询 u 和 v 的最近公共祖先
    int ask(int u, int v) {
        // 1. 保证 u 是深度较大的那个（在下面）
        if (d[u] < d[v]) swap(u, v);

        // 2. 将 u 上跳，直到和 v 同一层
        // i 从大到小试，类似二进制拆分
        for (int i = MAXLOG; i >= 0; --i) {
            // 如果 u 跳 2^i 步之后，深度依然 >= v 的深度，就跳
            if (d[u] - (1 << i) >= d[v]) {
                u = f[u][i];
            }
        }

        // 3. 如果跳到了同一层，且 u == v，说明 v 就是 u 的祖先
        if (u == v) return u;

        // 4. u 和 v 一起往上跳，直到 LCA 的下一层
        for (int i = MAXLOG; i >= 0; --i) {
            // 如果跳上去不一样，说明还没遇到 LCA，继续跳
            if (f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }

        // 5. 此时 u 和 v 的父亲就是 LCA
        return f[u][0];
    }
} lca;


void init(){
    std::cin >> n >> m >> root;
    for(int i = 1;i < n ;++i ) // i: 1->n
    {
        int u,v;
        std::cin >> u >> v;
        e.add2(u, v);
    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    lca.init(n,root);
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        cout << lca.ask(u,v) << "\n";
    }
    
    return 0;
}
