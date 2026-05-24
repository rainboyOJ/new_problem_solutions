/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-26 15:56:54
 */
#include <bits/stdc++.h>
using namespace std;

// 定义最大点数和边数
// N <= 150，拆点后点数约为 300，加上源汇点。2005 足够。
const int maxn = 2005; 
// M <= 6000，加上源点到X、Y到汇点的边，以及反向边。200005 足够。
const int maxe = 200005; 
const long long INF = 1e18;

// 路径还原辅助数组
// nxt[u] = v 表示在路径覆盖中，点 u 的下一个点是 v
int nxt[maxn]; 
// has_in[v] = true 表示点 v 在路径中作为了某个点的后继（即有入度）
// 用于寻找路径的起点（起点是没有入度的）
bool has_in[maxn];

// 递归打印路径
// 顺着 nxt 数组链表式输出
void print_path(int u) {
    cout << u << " ";
    if (nxt[u] != 0) {
        print_path(nxt[u]);
    }
}

// 链式前向星存图模板
struct linkList {
    // 边结构体：u起点, v终点, w容量, next下一条边索引
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt=0; // h数组存储每个点的第一条边索引

    // 构造函数：初始化头指针数组为 -1
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    // 遍历辅助函数：遍历点 u 的所有出边
    // 使用模板支持传入 lambda 表达式
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); // 回调函数参数：u, v, w
    }

    // 添加单向边
    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]}; // 头插法
        h[u] = edge_cnt++;
    }
    // 添加双向边（本题未使用）
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    // 重载 [] 方便直接访问边数组
    edge& operator[](int i){ return e[i]; }
    // 重载 () 方便获取 head[u]
    int operator()(int u){ return h[u]; }
} e; // 全局变量 e，存储图数据


// Dinic算法最大流模板 - 基于全局变量 e (linkList) 存图
struct Dinic {
    vector<int> level, iter;  // level: BFS分层图深度, iter: 当前弧优化游标
    int n;  // 总节点数
    
    // 初始化
    Dinic(int n) : n(n), level(n+5), iter(n+5) {
        // 注意：这里重置了全局的 linkList e
        // 如果有多次最大流计算，需注意 clear 问题
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));
    }
    
    // 添加网络流的边：包含正向边和反向边
    // u -> v 容量 cap
    // v -> u 容量 0
    void addEdge(int u, int v, long long cap) {
        e.add(u, v, cap);    // 索引 k (偶数)
        e.add(v, u, 0);      // 索引 k+1 (奇数)，互为反向边
    }
    
    // BFS 构建分层图 (Level Graph)
    // 目的：给每个点标号层级，限制 DFS 只能从低层流向高层，防止环流
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // 遍历 u 的所有邻接边
            e.for_each(u, [&](int from, int to, int cap) {
                // 如果边有残量 (cap > 0) 且终点未被分层
                if (cap > 0 && level[to] < 0) {
                    level[to] = level[u] + 1;
                    q.push(to);
                }
            });
        }
        
        return level[t] >= 0;  // 如果汇点 t 被分层了，说明存在增广路
    }
    
    // DFS 在分层图上寻找增广路 (多路增广)
    // u: 当前点, t: 汇点, preFlow:以此路径到达 u 的最大限制流量
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0; // 实际从 u 推送出去的流量
        
        // 当前弧优化：iter[u] 记录点 u 上次处理到的边
        // 避免重复遍历已经流满的废边
        for (int& cid = iter[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; 
            int to = edge.v;
            long long cap = edge.w;
            
            // 必须满足层级关系 level[v] = level[u] + 1 且有残量
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            // 递归查找后续路径的瓶颈流量
            long long tr = dfs(to, t, min(preFlow, cap));

            // 更新残量网络
            e[cid].w -= tr;       // 正向边容量减少
            e[cid ^ 1].w += tr;   // 反向边容量增加（利用异或1找到反向边）
            flow += tr;
            preFlow -= tr; // 剩余可分配流量减少
            
            if (preFlow == 0) break; // 如果流量分发完了，就结束循环
        }
        
        // 炸点优化 (Gap 优化的一种变体)
        // 如果从 u 出发流不出任何流量，说明 u 实际上已经废弃，从分层图中移除
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    // Dinic 主过程：求从 s 到 t 的最大流
    long long maxFlow(int s, int t) {
        long long flow = 0;
        // 只要能构建分层图（即存在增广路），就一直增广
        while (bfs(s, t)) {  
            // 每次 BFS 后，重置当前弧 iter 指向每个点的第一条边
            for (int i = 0; i <= n; i++) {
                iter[i] = e(i);  
            }
            
            // 多路增广，初始推入无穷大流量
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
};

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(0); cin.tie(0);
    
    int n, m;  // n个节点，m条边
    int s, t;  // 源点，汇点
    std::cin >> n >> m;
    
    // 设置源点为 0，汇点为 2*n+1
    // 拆点方案：点 i 拆为左部点 i 和 右部点 i+n
    s = 0;
    t = 2 * n + 1;
    
    Dinic dinic(t + 1);  // 创建 Dinic 实例，节点总数需包含汇点
    
    // 1. 构建原图的边 (对应二分图匹配边)
    // 原图 u -> v，在二分图中连线 左部u -> 右部v+n
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        dinic.addEdge(u, v + n, 1);  
    }

    // 2. 构建源点到左部点的边 (限制每个点作为路径起点/中间点流出 1 次)
    for(int i = 1; i <= n; ++i) 
        dinic.addEdge(s, i, 1);

    // 3. 构建右部点到汇点的边 (限制每个点作为路径终点/中间点流入 1 次)
    for(int i = 1; i <= n; ++i) 
        dinic.addEdge(n + i, t, 1);

    // 4. 计算最大二分匹配数 (即最大流)
    auto flow = dinic.maxFlow(s, t);

    // 5. 还原路径
    // 初始化辅助数组
    memset(nxt, 0, sizeof(nxt));
    memset(has_in, 0, sizeof(has_in));

    // 遍历所有左部点 u (1..n)
    for(int u = 1; u <= n; ++u) 
    {
        // 遍历 u 的所有出边
        for(int i = e.h[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            // 判断是否是匹配边：
            // 1. 终点 v 在右部点范围内 (n < v < t)
            // 2. e[i].w == 0 表示容量被用尽，即流量走了这条边 (匹配成功)
            if(v > n && v < t && e[i].w == 0) {
                int real_v = v - n; // 还原出实际点编号
                nxt[u] = real_v;    // 记录路径关系 u -> real_v
                has_in[real_v] = 1; // 标记 real_v 有入度（不是路径头）
                break; // 每个点出度最多为1，找到即可跳出
            }
        }
    }

    // 6. 输出路径
    // 遍历所有点，只要它没有入度 (has_in 为 false)，说明它是一条新路径的起点
    for (int i = 1; i <= n; i++) {
        if (!has_in[i]) {
            print_path(i); // 递归打印整条路径
            cout << endl;
        }
    }

    // 7. 输出最小路径数
    // 最小路径覆盖 = 顶点数 - 最大匹配数 (最大流)
    std::cout << n - flow << "\n";
    
    return 0;
}
