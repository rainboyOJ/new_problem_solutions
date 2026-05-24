/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-30 15:36:29
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

//oisnip_beginv-bcc.cpp
/*
代码细节解释：

1. **`std::vector<int> bcc[maxn]`**:
* 与 SCC 不同，SCC 中每个点只属于一个分量，可以用 `id[u]` 数组标记。
* 在点双 (v-BCC) 中，**割点**会同时属于多个 BCC。因此，我们通常用 `vector` 列表来保存每个 BCC 里有哪些点，而不是给每个点打唯一的 ID 标记。


2. **`st.push(u)` 与出栈逻辑**:
* 我们将点入栈。
* 当满足 `low[v] >= dfn[u]` 时，说明找到了一个以 `u` 为“顶端”的双连通分量。
* 我们不断 `pop` 直到弹出 `v`。
* **关键点**：`u` 也是这个分量的一部分，需要 `bcc[...].push_back(u)`，但是 **`u` 不能出栈**。因为 `u` 还是它父节点所在 BCC 的一部分（如果 `u` 不是根），或者是其他子树分支 BCC 的分割点。


3. **`e(u)`**:
* 这里保留了你代码中的 `e(u)` 写法，假设你已经定义了类似 `#define e(u) head[u]` 或者相应的函数来获取邻接表头指针。
这是一个求 **点双连通分量 (v-BCC)** 的模板。


主要区别在于：

1. **无向图 DFS**：需要传入 `father` 参数防止走回头路（或通过边索引判断）。
2. **出栈时机**：SCC 是在回溯完 `u` 后判断 `low[u] == dfn[u]` 出栈；而 BCC 是在处理子节点 `v` 时，若发现 `low[v] >= dfn[u]`，则说明 `v` 及其子树无法绕过 `u` 到达更早的祖先，此时 `u` 和 `v` 的子树构成一个点双。
3. **割点特性**：一个割点 (Articulation Point) 可以属于多个点双连通分量。

*/

struct TarjanBCC {
    int n, timer;
    std::stack<int> st;
    int dfn[maxn], low[maxn];
    int bcc_cnt; // BCC 计数
    bool is_cut[maxn];
    int root; //记录根节点
    std::vector<int> bcc[maxn]; // 存储每个 BCC 包含的具体节点

    void set(int _n) {
        n = _n;
        timer = bcc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(is_cut,0,sizeof(is_cut));

        while (!st.empty()) st.pop();
        for (int i = 0; i <= n; i++) bcc[i].clear();
    }

    // 无向图，需要 fa 参数防止直接走回父节点
    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        int child = 0;

        for (int i = e.h[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            
            if (v == fa) continue; // 无向图核心：不走回头路

            if (!dfn[v]) { // 如果 v 没被访问过
                dfs(v, u);
                child++;

                if(u != root  && low[v] >= dfn[u]) {
                    is_cut[u] = 1; 
                }
                
                // 更新 low 值
                low[u] = std::min(low[u], low[v]);

                // 核心判断：low[v] >= dfn[u] 说明 v 没法回到 u 的祖先
                // 此时 u 是割点（或者根），u-v 这条边及其下方的点构成一个 BCC
                if (low[v] >= dfn[u]) {
                    bcc_cnt++;
                    while (true) {
                        int node = st.top(); st.pop();
                        bcc[bcc_cnt].push_back(node);
                        if (node == v) break; // 只要弹到 v 为止
                    }
                    // 注意：u 也是这个 BCC 的一部分，但 u 可能属于多个 BCC，
                    // 所以 u 不能出栈，只是把 u 加入到当前 BCC 列表中
                    bcc[bcc_cnt].push_back(u);
                }
            } else if (dfn[v] < dfn[u]) { // 返祖边
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if( u == root && child > 1) 
            is_cut[u] =  1;
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i] && e.h[i] != -1 ) {
                // 此时栈为空，dfs 根节点
                // 根节点的特判通常包含在上述 dfs 逻辑中
                // 只有当图中有孤立点时，需额外注意栈内残留
                root = i;
                dfs(i, 0); 
                
                // 如果是孤立点或者根节点处理完栈里还有元素（极少见情况，视题目定义而定）
                // 实际上标准 v-BCC 逻辑中，上述 dfs 里的 if (low[v] >= dfn[u]) 会处理所有连通块
                // 唯一的例外是如果 i 是一个孤立点（没有边的点），它不会进入循环
                // 如果需要记录孤立点为 BCC，可以在这里补判
            }
        }
    }

    // helper 
    int cut_cnt() {
        int cnt = 0;
        for(int i = 1;i <= n ;++i ) // i: 1->n
            cnt += is_cut[i];
        return cnt;
    }
};
//oisnip_end

TarjanBCC tj;


void init(){
    e.reset();
    m = 0; //记录最大的点
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int u,v;
        std::cin >> u >> v;
        e.add2(u,v);
        if( m < u) m = u;
        if( m < v) m = v;
    }
    tj.set(m);
    tj.solve();

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int case_num = 0;
    while (1) {
        std::cin >> n;
        if( n == 0) break;
        init();

        // 计算答案
        ull ans = 1;
        int min_exits = 0;

        for(int i = 1 ; i <= tj.bcc_cnt ;i++) {

            int cut_cnt = 0;
            for( auto node : tj.bcc[i]) 
                cut_cnt += tj.is_cut[node];

            ull bcc_size = tj.bcc[i].size();
            
            if( cut_cnt == 0) {

                // 整个图是一个双连通分量，需要 2 个出口
                // 方案数为 C(size, 2)
                min_exits += 2;
                ans *= ( bcc_size *(bcc_size-1) / 2);
            }
            else if( cut_cnt == 1) {
                // 只有一个割点（叶子分量），需要 1 个出口
                // 方案数为 size - 1 (不能建在割点上)
                min_exits += 1;
                ans *= (bcc_size - 1);
            }
            // 割点数 >= 2，不需要额外出口
            // else {
            //     
            // }

        }

        std::cout << "Case " << ++case_num << ": ";
        std::cout << min_exits << " " << ans << "\n";
    }
    
    return 0;
}
