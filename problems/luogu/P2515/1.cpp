/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-30 19:41:41
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e2+5;
const int maxe = 5e2+5;
const int mod = 1e9+7;

int n,m;
int w[maxn];
int _V[maxn];
int scc_w[maxn]; // 缩点后的值
int scc_v[maxn]; // 缩点后的值
int father[maxn]; // father[i]
int dp[maxn][505];

int in_degree[maxn]; // 用于统计 SCC 的入度


bool connect[maxn][maxn]; // 用于scc去重边


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

linkList e2;

//oisnip_beginscc.cpp
struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; // SCC 的总数

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
    }

    // 有向图,不要加father参数
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e.h[u]; ~i ; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) { // 如果 v 没被访问过
                dfs(v);
                
                // 根据子节点的 low 值更新当前节点的 low 值
                low[u] = std::min(low[u], low[v]);
            } else if (in_stack[v]) { //返祖边, 如果 v 在栈中，说明构成了环
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        // 如果 dfn == low，说明找到了一个 SCC 的起始点
        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (1) {
                int v = st.top(); st.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt; // 标记所属 SCC 编号
                scc_w[scc_cnt] += w[v];
                scc_v[scc_cnt] += _V[v];
                if (v == u) break; // 直到找到起始点
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
};
//oisnip_end
TarjanScc tj;


void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
        std::cin >> w[i];
    for(int i = 1;i <= n ;++i ) // i: 1->n
        std::cin >> _V[i];
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> father[i];
        if( father[i] != 0)
            e.add(father[i],i); //反向建图
        // 父亲指向孩子
        // 如果孩子选, 那么父亲必须选
    }

}

// 树形背包 DP
void dfs_dp(int u) {
    // 初始化当前节点 u 的状态
    // 必须选 u 才能选它的子树，所以基础花费是 scc_w[u]，基础收益是 scc_v[u]
    // 其实就是一个子树都不选的状态,就是边界

    for(int j = scc_w[u] ;j <= m; j++)
        dp[u][j] = scc_v[u];

    for(int v : e2.adj(u)) {

        // 后序遍历
        dfs_dp(v);
        // 初始化当前节点 u 的状态
        // 必须选 u 才能选它的子树，所以基础花费是 scc_w[u]，基础收益是 scc_v[u]

        for(int j = m ;j >= scc_w[u];j--){

            // 枚举分给子树 v 的容量 k
            // k 不能超过 j - scc_w[u] (必须留出 u 自己的空间)
            // 就是 枚举组合的每个物品 : k: 0 1 2 ... 
            for(int k = 0 ;k <= j -scc_w[u] ; k ++)
            {
                dp[u][j] = std::max(dp[u][j] , dp[u][j - k] + dp[v][k]);
            }
        }

    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    init();

    // 2. Tarjan 缩点
    tj.set(n);
    tj.solve();

    // 3. 重建图 (建立 SCC 之间的树边)
    // 虚拟根节点 0，连接所有原本依赖 0 的点或者入度为 0 的 SCC
    // 我们可以直接根据原图的 father[i] 来判断连边
    // 如果原图 u->v，且 u,v 不在同一个 SCC，则连边 scc[u]->scc[v]
    
    // 记录入度以便处理森林的情况（或者简单地按照题意 father[i]=0 的连向 0）
    // 题目中 father[i] 是确定的依赖。
    // 如果 father[i] == 0，说明 i 依赖 0 (虚拟根)。
    // 如果 father[i] != 0，说明 i 依赖 father[i]。
    
    // 逻辑修正：
    // 我们需要把所有没有前驱的 SCC 连到 0 号节点上。
    // 因为 father[i] 给了明确的父子关系，我们可以这样建新图：
    // 遍历所有点 i：
    //   令 u = scc_id[father[i]] (如果 father[i]==0，则 u=0)
    //   令 v = scc_id[i]
    //   如果 u != v，则在新图中添加边 u -> v
    
    // 注意：0 号点本身不需要缩点，它是一个独立的虚拟点，scc_id[0] = 0
    // 0 号点重量为 0，价值为 0 


    //遍历每一条边
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int u = father[i]; // i 的父亲,表示i 依赖 father[i]
        int v = i;

        int u_scc = (u == 0) ? 0 : tj.scc_id[u];
        int v_scc = tj.scc_id[v];
        if( u_scc != v_scc && connect[u_scc][v_scc] == 0) 
        {
            connect[u_scc][v_scc] = 1;
            e2.add(u_scc,v_scc);
            in_degree[v_scc]++; // 统计入度
        }
    }

    // 坑点!!!! : 孤立的循环依赖环
    // 遍历所有 SCC，如果某个 SCC 在新图中入度为 0，说明它是一个孤立的团
    // 我们需要把它挂在虚拟根节点 0 下面，否则 DFS 进不去
    for(int i = 1; i <= tj.scc_cnt; i++) {
        if(in_degree[i] == 0) {
            // 这里不需要判重，因为如果 connect[0][i] 已经存在
            // 说明它本来就依赖 0，in_degree[i] 就不可能是 0 (如果是依赖0, 上面的循环会增加入度)
            // 所以这里直接连边即可
            e2.add(0, i);
        }
    }

    // 4. DP 求解
    // 0 号点也是一个合法的“物品”（重量0，价值0），从它开始 DFS
    // 这样能自动处理所有的联通分量
    dfs_dp(0);

    std::cout << dp[0][m] << "\n";

    
    return 0;
}
