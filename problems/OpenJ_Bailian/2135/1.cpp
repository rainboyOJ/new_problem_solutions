/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-12
 * Problem: POJ 2135 Farm Tour
 * Algorithm: Min-Cost Max-Flow (MCMF) - 最小费用最大流
 * * 教学说明:
 * 本题要求从起点 1 到终点 N 再回到 1 的最短路径，且不能走同一条路。
 * 这等价于：在图中找两条从 1 到 N 的不相交路径，使得总长度最小。
 * * 建模思路:
 * 1. 流量: 需要找两条路径，所以限制总流量 max_flow = 2。
 * 2. 容量: 每条边只能走一次，所以边的容量 capacity = 1。
 * 3. 费用: 希望路径最短，所以边的费用 cost = 路径长度。
 * 4. 求解: 跑最小费用最大流，当流量为 2 时，min_cost 即为答案。
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e4+5; // 点数 N <= 1000
const int maxe = 1e5+5; // 边数 M <= 10000 (需预留双向边及反向边的空间)
const long long INF = 1e18;
const int INF_INT = 0x3f3f3f3f;

int n, m;
int s, t; // 源点 汇点

// --- 存图模板: 链式前向星 (Chain Forward Star) ---
// 这种结构在图论竞赛中非常常用，空间效率高
struct linkList {
    // u: 起点, v: 终点, w: 容量(capacity), c: 费用(cost), next: 同起点的下一条边索引
    typedef struct {int u,v,w,c,next;} edge; 
    edge e[maxe];            // 存储所有边的数组
    int h[maxn], edge_cnt=0; // h[u] 存储节点 u 的第一条出边索引
    
    linkList(){
        reset();
    }

    // 初始化清空
    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    // 加边底层函数
    void add(int u, int v, int w=0, int c=0){
        e[edge_cnt] = {u, v, w, c, h[u]}; // 头插法：新边指向旧的头
        h[u] = edge_cnt++;                // 更新头指针指向新边
    }
    
    edge& operator[](int i){ return e[i]; }
} e;

// --- MCMF 算法模板 (核心) ---

struct MCMF {
    int dis[maxn];   // SPFA: 存储从源点 s 到各点的最小单位费用（最短路）
    int flow[maxn];  // SPFA: 记录到达该点时的瓶颈流量（路径上最小的剩余容量）
    int pre[maxn];   // Path: 记录最短路路径上的前驱节点，用于回溯
    int last[maxn];  // Path: 记录最短路路径上的入边索引，用于修改边容量
    bool vis[maxn];  // SPFA: 队列中的标记数组
    int n;           // 节点总数
    
    long long max_flow; // 最终结果：最大流量
    long long min_cost; // 最终结果：最小费用

    void init(int n) {
        e.reset();
        this->n = n;
    }
    
    // 添加一条有向边及其反向边
    // u -> v: 容量 cap, 单位费用 cost
    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);      // 正向边：正常添加
        
        // 反向边：容量为 0 (初始不可走)，费用为 -cost
        // 核心原理：反向边的负费用用于“反悔”。
        // 如果后续增广流走了 v->u，相当于抵消了之前 u->v 的流量，并退回了 cost 费用。
        e.add(v, u, 0, -cost);       
    }
    
    // SPFA 算法：在残留网络中寻找单位费用最小的增广路
    // 返回值: true 表示找到了增广路(能到达汇点 t)，false 表示无法再增广
    bool spfa(int s, int t) {
        // 初始化：距离无穷大，流量无穷大，清空标记
        for(int i = 0; i <= n+1; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        
        queue<int> q;
        dis[s] = 0;      // 起点费用为 0
        vis[s] = 1;      // 入队标记
        pre[t] = -1;     // 标记汇点的前驱为 -1，用于最后判断是否可达
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0; // 出队，清除标记，允许再次入队（SPFA 特性）
            
            // 遍历 u 的所有出边
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v;       // 目标点
                int cap = e[i].w;     // 边的剩余容量
                int cost = e[i].c;    // 边的单位费用

                // 松弛操作 (Relaxation)：
                // 1. cap > 0: 必须有剩余容量才能走
                // 2. dis[v] > dis[u] + cost: 发现了费用更小的路径
                if (cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;      // 更新最小费用
                    pre[v] = u;                  // 记录前驱节点
                    last[v] = i;                 // 记录通过哪条边过来的
                    flow[v] = min(flow[u], cap); // 维护路径上的最小剩余容量（木桶效应）
                    
                    if (!vis[v]) { // 如果 v 不在队列中，则入队
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return pre[t] != -1; // 如果汇点的前驱被更新了，说明找到了路
    }
    
    // 主求解函数
    void solve(int s, int t) {
        max_flow = 0;
        min_cost = 0;
        
        // 循环：只要还能找到费用最小的路径，就一直增广
        while (spfa(s, t)) {
            int now = t;
            int f = flow[t]; // 本次增广能增加的流量（由路径上的最小容量决定）
            
            max_flow += f;                     // 累加流量
            min_cost += (long long)f * dis[t]; // 累加费用 = 流量 * 单价
            
            // 回溯路径，更新残留网络
            while (now != s) {
                int edge_idx = last[now]; // 获取进入 now 的边
                
                e[edge_idx].w -= f;       // 正向边容量减少
                e[edge_idx ^ 1].w += f;   // 反向边容量增加 (利用异或 1 找到成对的边)
                
                now = pre[now];           // 向前移动到前驱节点
            }
        }
    }
} mcmf;

// --- 针对 Farm Tour 问题的初始化逻辑 ---

void init(){
    // 输入 N (田地数/节点数) 和 M (路径数/边数)
    if(!(cin >> n >> m)) return;

    // 修改点：为了限制总流量为 2，我们引入超级源点和超级汇点
    // 超级源点 s = 0, 超级汇点 t = n + 1
    s = 0;
    t = n + 1;

    // 初始化 MCMF，注意节点范围变大了，传入 t 确保数组边界安全
    mcmf.init(t); 
    
    // 1. 添加超级源点 -> 1 (House) 的边
    // 容量为 2 (限制找两条路径), 费用为 0
    mcmf.addEdge(s, 1, 2, 0);

    // 2. 添加 N (Barn) -> 超级汇点 的边
    // 容量为 2, 费用为 0
    mcmf.addEdge(n, t, 2, 0);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // 关键建图逻辑：
        // 题目给的是无向边，长度为 w。
        // 在网络流中，无向边意味着可以从 u 到 v，也可以从 v 到 u。
        // 因此我们建立两条有向边：
        
        // 1. u -> v: 容量 1 (只能走一次), 费用 w (距离)
        mcmf.addEdge(u, v, 1, w); 
        
        // 2. v -> u: 容量 1 (只能走一次), 费用 w (距离)
        mcmf.addEdge(v, u, 1, w); 
    }
}

int main() {
    // 优化 C++ 标准流 I/O 速度，竞赛必备
    ios::sync_with_stdio(0); cin.tie(0);
    
    init(); // 读入数据并建图
    
    // 求解最小费用最大流
    // 算法会自动寻找两条路径（流量为2），且总费用最小
    mcmf.solve(s, t);
    
    // 输出最小费用（即 FJ 往返的最短总路程）
    cout << mcmf.min_cost << "\n";
    
    return 0;
}
