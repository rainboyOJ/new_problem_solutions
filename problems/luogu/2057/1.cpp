/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-25 10:07:50
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边 (注意：要是题目边数的2倍)
const long long INF = 1e18;

int n,m;
int s,t; // 源点 汇点
int a[maxn];

// 存图的模板

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


// Dinic算法最大流模板 - 基于linkList存图
struct Dinic {
    vector<int> level, cur;  // level: BFS分层, cur: 当前弧优化
    int n;  // 节点数
    
    void init(int n) {
        // 重置linkList
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));

        level.resize(n+5);
        cur.resize(n+5);
        this->n = n;
    }
    
    // 添加边：从u到v，容量为cap
    // 使用技巧：正向边和反向边的索引相差1，通过异或1来找到对应边
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边，w字段存储容量
        e.add(v, u, 0);      // 反向边，容量为0
    }
    
    // BFS分层，构建层次图
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // 使用linkList的遍历方式
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v, cap = e[i].w;
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        
        return level[t] >= 0;  // 返回是否能到达汇点
    }
    
    // DFS寻找增广路
    // 到达点u流量为preFlow
    // 计算从点u出发的最大流，到达点t
    // 本质是一个DAG 上的dp
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        
        // 当前弧优化：从cur[u]开始遍历
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; // 当前弧优化
            int to = edge.v;
            long long cap = edge.w;
            
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            long long tr = dfs(to, t, min(preFlow, cap));

            // 更新容量
            e[cid].w -= tr ;     // 正向边容量减少
            e[cid ^ 1].w += tr; // 反向边容量增加（利用异或找到反向边）
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        
        // 炸点优化
        // 剪枝：取掉增广完毕的点
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    // 求从s到t的最大流
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {  // 能够分层
            // 当前弧优化重置：将cur设置为每个节点的第一条边
            for (int i = 0; i <= n; i++) {
                cur[i] = e.h[i];  // 使用linkList的operator()获取head[i]
            }
            
            // 多路增广
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

void init(){
    std::cin >> n >> m;
    s = 0;
    t = n+1;

    dinic.init(t+5);
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int sleep;
        std::cin >> sleep;

        if( sleep ) {
            dinic.addEdge(s, i, 1);
        }
        else
            dinic.addEdge(i, t, 1);

    }
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        dinic.addEdge(u, v, 1);
        dinic.addEdge(v,u,1);
    }

}

// 使用示例：
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    
    cout << dinic.maxFlow(s,t) << "\n";
    
    return 0;
}

/*
复杂度分析：
- 时间复杂度：O(V²E) 一般情况下表现很好，对于单位容量网络是O(min(V^(2/3), E^(1/2)) * E)
- 空间复杂度：O(V + E)

使用说明：
1. 创建Dinic实例：Dinic dinic(n);
2. 添加边：dinic.addEdge(u, v, cap);
3. 求最大流：long long flow = dinic.maxFlow(source, sink);

注意事项：
- 节点编号从0开始
- 如果题目给的是1-indexed，记得转换
- 容量使用long long防止溢出
- 无向边需要添加两条有向边
*/
