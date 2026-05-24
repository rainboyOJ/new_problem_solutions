/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-09 10:51:03
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e3+5;
const int maxe = 4e3+5; // 边数稍大，保证空间充足
int n, m;
int a[maxn]; // 每个人的花费

//oisnip_beginlinklist.cpp
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt=0;
    
    linkList(){
        // 构造函数保持空或最小初始化，具体重置交给 init(n)
        edge_cnt = 0;
        // 注意：全局变量默认 h 为 0 或 -1 需要显式处理，这里留给 init 处理
    }

    // 优化：传入 n 只清空用到部分，避免 TLE
    void init(int _n) {
        edge_cnt = 0;
        for(int i = 0; i <= _n; ++i) h[i] = -1;
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

#ifdef __cpp_range_based_for
    // 策略A: 获取整条边
    struct UseEdge {
        using ReturnType = edge&; 
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };

    // 策略B: 只获取邻接点v
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
//oisnip_end

//oisnip_beginscc.cpp
struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; 

    // 优化：只重置 0~n 的部分
    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        for(int i = 0; i <= n; ++i) {
            dfn[i] = 0;
            low[i] = 0;
            in_stack[i] = false;
            scc_id[i] = 0;
        }
        while (!st.empty()) st.pop();
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e.h[u]; ~i ; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) { 
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (in_stack[v]) { 
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (1) {
                int v = st.top(); st.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt; 
                if (v == u) break; 
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
} scc;
//oisnip_end

// 全局变量用于 DAG 计算
int scc_min_cost[maxn]; // 每个 SCC 内的最小花费
int scc_in_degree[maxn]; // 每个 SCC 的入度

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    while(cin >> n >> m) {
        // 1. 读入花费
        for(int i = 1; i <= n; ++i) cin >> a[i];

        // 2. 初始化图并读入边
        e.init(n); // 使用优化后的 init
        for(int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            e.add(u, v);
        }

        // 3. 计算 SCC
        scc.set(n);
        scc.solve();

        // 4. 初始化 DAG 统计数组
        // 注意 scc_cnt 是从 1 开始计数的
        for(int i = 1; i <= scc.scc_cnt; ++i) {
            scc_min_cost[i] = 0x3f3f3f3f; // INF
            scc_in_degree[i] = 0;
        }

        // 5. 遍历每个点，维护 SCC 信息和构建 DAG
        for(int u = 1; u <= n; ++u) {
            int u_id = scc.scc_id[u];
            
            // 维护当前 SCC 的最小花费
            scc_min_cost[u_id] = min(scc_min_cost[u_id], a[u]);

            // 使用 linkList 的 range-based for 语法糖遍历邻接点
            // e.adj(u) 返回的是邻接点 v 的迭代器
            for(int v : e.adj(u)) {
                int v_id = scc.scc_id[v];
                if(u_id != v_id) {
                    scc_in_degree[v_id]++;
                }
            }
        }

        // 6. 统计结果：累加入度为 0 的 SCC
        int ans_people = 0;
        int ans_cost = 0;
        for(int i = 1; i <= scc.scc_cnt; ++i) {
            if(scc_in_degree[i] == 0) {
                ans_people++;
                ans_cost += scc_min_cost[i];
            }
        }

        cout << ans_people << " " << ans_cost << "\n";
    }

    return 0;
}
