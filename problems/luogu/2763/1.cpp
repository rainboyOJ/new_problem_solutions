/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-11 21:31:11
 * * 题目: P2763 试题库问题
 * 算法: Dinic 最大流
 * 建图模型: 二分图多重匹配 (源点 -> 题目 -> 类型 -> 汇点)
 */

#include <bits/stdc++.h>
using namespace std;

// --- 常量定义 ---
const int maxn = 1e6+5; // 最大点数 (根据题目数据范围调整，本题其实1000多就够，这里留足余量)
const int maxe = 2e6+5; // 最大边数 (注意：网络流加双向边，大小至少要是题目逻辑边数的2倍)
const long long INF = 1e18; // 无穷大，用于流量初始化

// --- 全局变量 ---
int n, k, m;   // n: 试题总数, k: 试题类型数, m: 需要选出的总题数
int s, t;      // s: 源点编号, t: 汇点编号
int kcnt[maxn]; // 记录每种类型需要的题目数量

// --- 存图模板：链式前向星 (Chain Forward Star) ---
struct linkList {
    typedef struct {int u, v, w, next;} edge;
    edge e[maxe];            // 存储边的数组
    int h[maxn], edge_cnt=0; // h[]存储每个点的第一条边下标, edge_cnt计数器
    
    linkList(){
        edge_cnt = 0;
        memset(h, -1, sizeof(h)); // 初始化头指针为 -1
    }

    // 遍历点 u 周围所有出边的辅助函数 (虽然main里没直接用，但属于模板好习惯)
    template<typename U>
    void for_each(int u, U func){
        for(int i = h[u]; i != -1; i = e[i].next)
            func(e[i].u, e[i].v, e[i].w); // 回调函数处理 u, v, w
    }

    // 添加一条单向边
    void add(int u, int v, int w=0){
        // 新边的 u, v, w, 以及指向同起点的上一条边 h[u]
        e[edge_cnt] = {u, v, w, h[u]};
        h[u] = edge_cnt++; // 更新头指针
    }
    
    // 添加无向边 (本题未用，网络流通常用 addEdge 处理正反边)
    void add2(int u, int v, int w=0){
        add(u, v, w);
        add(v, u, w);
    }
    
    // 运算符重载，方便像数组一样访问边 e[i]
    edge& operator[](int i){ return e[i]; }
    // 运算符重载，方便直接获取 h[u]
    int operator()(int u){ return h[u]; }
} e;


// --- Dinic 算法最大流模板 ---
struct Dinic {
    vector<int> level, iter;  // level: BFS分层深度, iter: 当前弧优化指针
    int n;  // 当前图的节点总数
    
    // 初始化函数，多组数据时必须调用
    void init(int n) {
        // 重置链式前向星
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));

        // 调整 vector 大小
        level.resize(n + 5);
        iter.resize(n + 5);
        this->n = n;
    }
    
    // 添加网络流的边：正向边容量 cap，反向边容量 0
    // 技巧：正向边下标为偶数(i)，反向边为奇数(i^1)
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边，w 存储容量
        e.add(v, u, 0);      // 反向边，容量初始为 0
    }
    
    // BFS 分层：构建层次图 (Level Graph)
    // 作用：保证增广路径是最短的，并检测是否还能到达汇点
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1); // 初始化层级为 -1 (未访问)
        queue<int> q;
        level[s] = 0; // 源点层级为 0
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // 遍历所有出边
            for(int i = e.h[u]; ~i; i = e[i].next) {
                int v = e[i].v, cap = e[i].w;
                // 如果边有剩余容量 且 v 未被访问过
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1; // 标记层级
                    q.push(v);
                }
            }
        }
        
        return level[t] >= 0;  // 如果汇点 t 被标记了层级，说明 s->t 还有路
    }
    
    // DFS 寻找增广路 (多路增广)
    // u: 当前点, t: 汇点, preFlow: 到达 u 的可用流量
    // 返回值: 从 u 出发实际能流向 t 的最大流量
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow; // 到达汇点或无流量
        long long flow = 0;
        
        // --- 当前弧优化 ---
        // 每次 DFS 从 iter[u] 开始，而不是 e.h[u]。
        // 跳过那些已经增广满的边，避免重复扫描。
        for (int& cid = iter[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid];
            int to = edge.v;
            long long cap = edge.w;
            
            // 必须是分层图中 "下一层" 的点，且有剩余容量
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            // 递归寻找增广路，流量受限于当前边容量和之前的流量
            long long tr = dfs(to, t, min(preFlow, cap));

            // --- 更新残余网络 ---
            e[cid].w -= tr;       // 正向边容量减少
            e[cid ^ 1].w += tr;   // 反向边容量增加 (利用异或找到反向边)
            
            flow += tr;           // 累计流出的总流量
            preFlow -= tr;        // 剩余可用流量减少
            
            if (preFlow == 0) break; // 如果流量用尽，就不必继续遍历其他边了
        }
        
        // --- 炸点优化 (剪枝) ---
        // 如果从 u 出发流不出任何流量，说明 u 对于当前分层图是 "死胡同"
        // 标记 level 为 -1，后续 BFS/DFS 不再访问
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    // 求从 s 到 t 的最大流
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {  // 只要能构建出层次图 (s还能到t)
            // 重置当前弧 iter，指向每个点的第一条边
            for (int i = 0; i <= n; i++) {
                iter[i] = e(i);  
            }
            
            // 进行多路增广
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// --- 初始化与建图逻辑 ---
void init(){
    std::cin >> k >> n;
    
    // 节点编号规划：
    // 源点 s: 0
    // 题目节点: 1 ~ n
    // 类型节点: n+1 ~ n+k  (为了区分题目和类型，给类型加偏移量 n)
    // 汇点 t: n+k+1
    
    dinic.init(n + k + 2); // 初始化足够大的空间
    s = 0;
    t = k + n + 1;

    // 1. 构建 [类型节点 -> 汇点] 的边
    // 限制：每个类型 i 需要选出的题目数量为 kcnt[i]
    for(int i = 1; i <= k; ++i) 
    {
        std::cin >> kcnt[i];
        m += kcnt[i]; // 统计需要的总题数，用于最后判断是否有解

        // 类型 i 的节点编号是 n+i
        dinic.addEdge(n+i, t, kcnt[i]);
    }

    // 2. 构建 [题目节点 -> 类型节点] 和 [源点 -> 题目节点] 的边
    for(int i = 1; i <= n; ++i) 
    {
        int p; // 该题目所属类型的数量
        std::cin >> p;

        while (p--) {
            int type_id;
            std::cin >> type_id;
            // 边：题目 i -> 类型 type_id
            // 容量 1：这道题如果是该类型，可以贡献 1 的流量
            dinic.addEdge(i, n + type_id, 1);
        }
        
        // 边：源点 s -> 题目 i
        // 容量 1：限制每道题最多只能被选 1 次 (无论它有多少个类型)
        dinic.addEdge(s, i, 1);
    }
}

// 主函数
int main() {
    // 关闭同步，加速 I/O
    ios::sync_with_stdio(0); cin.tie(0);
    
    init(); // 读入数据并建图
    
    // 计算最大流
    long long flow = dinic.maxFlow(s, t);
    
    // 如果最大流 != 需要的总题数，说明无法满足需求
    if( flow != m ) {
        cout << "No Solution!\n";
    }
    else {
        // --- 构造并输出方案 ---
        // ans[i] 用来存储属于 "类型 i" 的题目编号列表
        vector<int> ans[25]; 

        // 遍历所有题目节点 (编号 1 到 n)
        for(int u = 1; u <= n; ++u) 
        {
            // 遍历题目 u 的所有出边
            for(int i = e.h[u]; ~i; i = e[i].next) {
                int v = e[i].v; // 边的终点

                // 判断条件：
                // 1. 终点 v 是类型节点 (范围在 n+1 到 n+k 之间)
                // 2. e[i].w == 0 (说明这条边容量被耗尽了，流量走了这里，即被选中)
                if( v > n && v <= n+k && e[i].w == 0) {
                    ans[v - n].push_back(u); // 记录题目 u 属于类型 v-n
                    break; // 一道题只能被分配到一个类型，找到后即可跳出当前题目的边遍历
                }
            }
        }

        // 按要求格式输出：类型编号: 题目编号 ...
        for(int i = 1; i <= k; ++i) 
        {
            cout << i << ":";
            for( auto p : ans[i] ) cout << " " << p;
            std::cout << "\n";
        }
    }
    
    return 0;
}

/*
复杂度分析：
- Dinic 算法时间复杂度：O(V²E)。
- 对于二分图匹配类型的网络（单位容量网络），复杂度为 O(E * sqrt(V))，效率非常高。
- 空间复杂度：O(V + E)。
*/
