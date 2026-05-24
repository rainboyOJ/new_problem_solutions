/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-11 22:34:24
 * 题目: P2071 座位安排
 * 算法: Dinic 最大流
 * 模型: 二分图多重匹配
 */

#include <bits/stdc++.h>
using namespace std;

// --- 常量定义 ---
const int maxn = 1e6+5; // 最大点数 (根据题目数据范围设定)
const int maxe = 2e6+5; // 最大边数 (网络流双向边，通常是题目逻辑边数的2倍以上)
const long long INF = 1e18;

// --- 全局变量 ---
int n, m;
int s, t; // s: 源点, t: 汇点
int a[maxn];

// --- 存图模板: 链式前向星 (Chain Forward Star) ---
// 这种结构在图论和网络流中非常常用，效率高，空间紧凑
struct linkList {
    typedef struct {int u, v, w, next;} edge;
    edge e[maxe];            // 边数组
    int h[maxn], edge_cnt=0; // h[u]存储点u的第一条边索引
    
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h)); // 初始化头指针为 -1
    }

    // 遍历点 u 周围点的辅助函数
    template<typename U>
    void for_each(int u, U func){
        for(int i = h[u]; i != -1; i = e[i].next)
            func(e[i].u, e[i].v, e[i].w); // u v w
    }

    // 加边函数：头插法
    void add(int u, int v, int w=0){
        e[edge_cnt] = {u, v, w, h[u]};
        h[u] = edge_cnt++;
    }
    
    // 添加无向边 (网络流中一般不用这个，而是手动加正反两条边)
    void add2(int u, int v, int w=0){
        add(u, v, w);
        add(v, u, w);
    }
    
    // 运算符重载，方便下标访问
    edge& operator[](int i){ return e[i]; }

    // --- C++ 语法糖 (Range-based for loop 支持) ---
    // 这部分让遍历边可以写成 for(auto& edge : list(u)) 的形式
    // 虽然下面的 Dinic 实现中主要用了传统的 for 循环，但这是很好的模板特性
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

// --- Dinic 算法模板 ---
// 相比 EK 算法，Dinic 通过 BFS 分层和 DFS 多路增广，效率更高
struct Dinic {
    vector<int> level, cur;  // level: BFS分层深度, cur: 当前弧优化指针
    int n;  // 节点总数
    
    // 初始化 Dinic 结构
    void init(int n) {
        // 重置链式前向星
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));

        // 调整 vector 大小
        level.resize(n+5);
        cur.resize(n+5);
        this->n = n;
    }
    
    // 添加网络流的边
    // u->v 容量 cap, v->u 容量 0 (反向边)
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边，索引为偶数 (0, 2, 4...)
        e.add(v, u, 0);      // 反向边，索引为奇数 (1, 3, 5...)
    }
    
    // BFS 构建层次图 (Level Graph)
    // 作用：确保增广路是“最短”的，防止绕圈，保证复杂度
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1); // 初始化所有点层级为 -1
        queue<int> q;
        level[s] = 0; // 源点层级为 0
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // 遍历 u 的所有出边
            for(int i = e.h[u]; ~i; i = e[i].next) {
                int v = e[i].v, cap = e[i].w;
                // 如果有残余容量 且 v 未访问过
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1; // 标记层级
                    q.push(v);
                }
            }
        }
        
        return level[t] >= 0;  // 如果能从 s 走到 t，返回 true
    }
    
    // DFS 寻找增广路 (多路增广)
    // u: 当前点, t: 汇点, preFlow: 目前推过来的可用流量
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow; // 到达汇点或没流量了
        long long flow = 0;
        
        // --- 当前弧优化 (Current Arc Optimization) ---
        // 这里的 &cid = cur[u] 非常关键
        // 下次访问 u 时，直接从上次处理到的边开始，跳过已经流满的边
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; 
            int to = edge.v;
            long long cap = edge.w;
            
            // 必须是分层图中下一层的点 (level[to] == level[u] + 1)
            // 且必须有剩余容量
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            // 递归向下推流
            long long tr = dfs(to, t, min(preFlow, cap));

            // 更新残余网络
            e[cid].w -= tr;       // 正向边容量减少
            e[cid ^ 1].w += tr;   // 反向边容量增加 (异或 1 找到反向边)
            
            flow += tr;           // 累计流出的流量
            preFlow -= tr;        // 剩余可用流量减少
            
            if (preFlow == 0) break; // 流量用尽，不需要再遍历后面的边了
        }
        
        // --- 炸点优化 ---
        // 如果流不出去了，将 level 设为 -1，后续 BFS 不再访问该点
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    // 计算最大流的主函数
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {  // 只要还能分层 (即 s 能到达 t)
            // 重置当前弧，让每个点从第一条边开始尝试
            for (int i = 0; i <= n; i++) {
                cur[i] = e.h[i];  
            }
            
            // 进行多路增广
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// --- 建图与初始化逻辑 ---
void init(){
    std::cin >> n; // 读取 N (排数)
    
    // 节点映射规划：
    // 源点 s: 0
    // 人节点: 1 到 2*n (共 2N 个人)
    // 座位排节点: 2*n + 1 到 2*n + n (共 N 排)
    // 汇点 t: 3*n + 1
    
    s = 0;
    t = 3*n + 1;
    dinic.init(t + 5); // 初始化 Dinic 结构，分配空间

    // 1. 处理 "人"
    for (int i = 1; i <= 2*n; i++) {
        // 源点 -> 人 (容量 1)
        // 含义：每个人只能被安排一个座位
        dinic.addEdge(s, i, 1);

        int t1, t2; // 每个人想坐的两个排的编号
        std::cin >> t1 >> t2;
        
        // 人 -> 座位排 t1 (容量 1)
        // 注意：座位排的节点编号需要加上偏移量 2*n
        dinic.addEdge(i, 2*n + t1, 1);
        
        // 人 -> 座位排 t2 (容量 1)
        dinic.addEdge(i, 2*n + t2, 1);
    }

    // 2. 处理 "座位排"
    for(int i = 1; i <= n; ++i) 
    {
        // 座位排 -> 汇点 (容量 2)
        // 含义：每排座位最多只能坐 2 个人
        // 注意：座位排节点编号是 2*n + i
        dinic.addEdge(2*n + i, t, 2);
    }
}

// 主函数
int main() {
    ios::sync_with_stdio(0); cin.tie(0); // 加速 IO
    init(); // 读入数据并建图
    
    // 输出最大流，即最多能满足多少人
    cout << dinic.maxFlow(s,t) << "\n";
    
    return 0;
}
