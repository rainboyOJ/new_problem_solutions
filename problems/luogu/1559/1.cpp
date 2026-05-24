/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-12 15:40:09
 * Problem: P1559 运动员最佳匹配问题
 * Algorithm: Min-Cost Max-Flow (MCMF) - 最小费用最大流
 * * 教学说明:
 * 本题要求为 N 男 N 女配对，使得总优势值最大。
 * 这是一个典型的 "二分图最大权完美匹配" 问题。
 * * 建模思路:
 * 1. 源点 S -> 所有男运动员 (容量1, 费用0): 限制每个男生只能选一个搭档。
 * 2. 所有女运动员 -> 汇点 T (容量1, 费用0): 限制每个女生只能选一个搭档。
 * 3. 男 i -> 女 j: 容量 1, 费用 -value。
 * * 为什么要取负? 
 * MCMF 算法求的是 "最小费用"。
 * 题目要求 "最大优势"。
 * 数学上: max(Sum) = -min(-Sum)。
 * 所以我们将权值取反，求出最小费用后，再取反回来就是最大优势。
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 最大点数 (根据实际情况调整，本题N=20，其实很小)
const int maxe = 2e6+5; // 最大边数 (注意：网络流加双向边，空间要预留足)
const long long INF = 1e18;
const int INF_INT = 0x3f3f3f3f;

int n,m;
int s,t; // 源点 汇点
int P[30][30]; // 男对女的优势矩阵
int Q[30][30]; // 女对男的优势矩阵

// --- 存图模板: 链式前向星 (Chain Forward Star) ---
// 这种结构在图论竞赛中非常常用，空间效率高，遍历速度快

struct linkList {
    // u:起点, v:终点, w:容量(capacity), c:费用(cost), next:下一条边索引
    typedef struct {int u,v,w,c,next;} edge; 
    edge e[maxe];            // 边数组
    int h[maxn],edge_cnt=0;  // h[u]存储节点u的第一条出边，cnt是边计数器
    
    linkList(){
        reset();
    }

    // 初始化清空
    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    // 加边核心函数 (头插法)
    void add(int u,int v,int w=0, int c=0){
        e[edge_cnt] = {u,v,w,c,h[u]}; // 新边的next指向旧的头
        h[u] = edge_cnt++;            // 更新头指针指向新边
    }
    
    // 运算符重载，方便像数组一样访问边 e[i]
    edge& operator[](int i){ return e[i]; }
} e;


// --- MCMF 算法模板 (核心) ---
// 最小费用最大流算法
// 核心思想：在保证流量增广的同时，总是寻找单位费用最小的路径进行增广

struct MCMF {
    int dis[maxn];   // SPFA: 存储从源点s到各点的最小单位费用（最短路距离）
    int flow[maxn];  // SPFA: 记录到达该点时的瓶颈流量（路径上最小剩余容量）
    int pre[maxn];   // Path: 记录路径上的前驱节点，用于回溯
    int last[maxn];  // Path: 记录路径上的入边索引，用于修改容量
    bool vis[maxn];  // SPFA: 队列中的标记数组
    int n;           // 节点总数
    
    long long max_flow; // 最终结果：最大流量
    long long min_cost; // 最终结果：最小费用

    // 初始化函数
    void init(int n) {
        e.reset();
        this->n = n;
    }
    
    // 添加网络流的边
    // u->v: 容量 cap, 单位费用 cost
    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);      // 正向边：正常添加
        // 反向边：容量初始为0，费用为 -cost (负费用用于"反悔")
        e.add(v, u, 0, -cost);       
    }
    
    // SPFA 算法：在残量网络中寻找单位费用最小的增广路
    // 返回值: true 表示找到了路径(能到达汇点 t)，false 表示结束
    bool spfa(int s, int t) {
        // 初始化：距离无穷大，流量无穷大，清空标记
        for(int i = 0; i <= n+1; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        
        queue<int> q;
        dis[s] = 0;      // 起点费用为0
        vis[s] = 1;      // 入队标记
        pre[t] = -1;     // 标记汇点前驱为-1，用于判断是否可达
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0; // 出队清除标记，SPFA特性允许节点多次入队
            
            // 遍历 u 的所有出边
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v;       // 目标点
                int cap = e[i].w;     // 剩余容量
                int cost = e[i].c;    // 单位费用

                // 松弛操作 (Relaxation)：
                // 1. cap > 0: 必须有剩余容量才能走
                // 2. dis[v] > dis[u] + cost: 发现了费用更小的路径
                if (cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;      // 更新最小费用
                    pre[v] = u;                  // 记录前驱节点
                    last[v] = i;                 // 记录入边
                    flow[v] = min(flow[u], cap); // 维护路径上的瓶颈流量
                    
                    if (!vis[v]) { // 若 v 不在队列中，则入队
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        
        return pre[t] != -1; // 如果汇点的前驱被更新了，说明找到了路
    }
    
    // 主求解函数
    // 不断寻找最短路（最小费用路径），直到无法增广
    void solve(int s, int t) {
        max_flow = 0;
        min_cost = 0;
        
        // 循环：只要还能找到费用最小的路径，就一直增广
        while (spfa(s, t)) {
            int now = t;
            int f = flow[t]; // 本次增广的流量
            
            max_flow += f;                     // 累加流量
            min_cost += (long long)f * dis[t]; // 累加费用 = 流量 * 单价
            
            // 回溯路径，更新残量网络
            while (now != s) {
                int edge_idx = last[now]; // 获取进入 now 的边
                
                e[edge_idx].w -= f;       // 正向边容量减少
                e[edge_idx ^ 1].w += f;   // 反向边容量增加 (异或1找到成对的边)
                
                now = pre[now]; // 向前移动到前驱节点
            }
        }
    }
} mcmf;

void init(){
    // 1. 读入数据
    std::cin >> n;
    // 读入 P 矩阵 (男对女的优势)
    for(int i = 1;i <= n ;++i ) 
    {
        for(int j = 1;j <= n ;++j ) 
        {
            std::cin >> P[i][j];
        }
    }

    // 读入 Q 矩阵 (女对男的优势)
    for(int i = 1;i <= n ;++i ) 
    {
        for(int j = 1;j <= n ;++j ) 
        {
            std::cin >> Q[i][j];
        }
    }

    // 2. 节点编号规划
    // 源点 s: 0
    // 男运动员: 1 ~ n
    // 女运动员: n+1 ~ 2n
    // 汇点 t: 2n+1
    s = 0;
    t = 2*n + 1;
    mcmf.init(t); // 初始化 MCMF，传入最大节点编号

    // 3. 建图
    for(int i = 1;i <= n ;++i ) 
    {
        // 源点 -> 男运动员 i
        // 容量 1: 限制每个男生只能参与 1 个配对
        // 费用 0: 不产生额外价值
        mcmf.addEdge(s, i, 1, 0);

        // 女运动员 j -> 汇点
        // 容量 1: 限制每个女生只能参与 1 个配对
        // 费用 0
        // 注意：女生的节点编号是 i+n
        mcmf.addEdge(i+n, t,1,0);

        // 男运动员 i -> 女运动员 j
        for(int j = 1;j <= n ;++j ) 
        {
            // 计算双方配对的优势值
            int val = P[i][j] * Q[j][i];
            
            // 容量 1: 这种配对关系只能用一次
            // 费用 -val: 关键点！
            // 因为算法求的是"最小费用"，我们要求"最大优势"。
            // 存负数后，算法会找累加和最小的路径（即绝对值最大的路径）。
            mcmf.addEdge(i,j+n,1,-val);
        }
    }
    
}

// 使用示例：
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init(); // 读入数据并建图
    
    mcmf.solve(s, t); // 运行最小费用最大流
    
    // 输出结果时，记得取反回来
    // 因为存的是负费用，计算出的 min_cost 是负数
    // -min_cost 才是我们需要的最大优势和
    std::cout << -mcmf.min_cost << "\n";
    
    return 0;
}
