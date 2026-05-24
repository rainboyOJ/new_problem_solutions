#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边 (注意：要是题目边数的2倍)
const long long INF = 1e18;

// 存图的模板
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
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
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e;


// Dinic算法最大流模板 - 基于linkList存图
struct Dinic {
    vector<int> level, iter;  // level: BFS分层, iter: 当前弧优化
    int n;  // 节点数
    
    // 初始化，n为节点数（节点编号从0开始）
    Dinic(int n) : n(n), level(n+5), iter(n+5) {
        // 重置linkList
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));
    }
    
    // 添加边：从u到v，容量为cap
    // 使用技巧：正向边和反向边的索引相差1，通过异或1来找到对应边
    void addEdge(int u, int v, long long cap) {
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
            e.for_each(u, [&](int from, int to, int cap) {
                if (cap > 0 && level[to] < 0) {
                    level[to] = level[u] + 1;
                    q.push(to);
                }
            });
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
        
        // 当前弧优化：从iter[u]开始遍历
        for (int& cid = iter[u]; cid != -1; cid = e[cid].next) {
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
            // 当前弧优化重置：将iter设置为每个节点的第一条边
            for (int i = 0; i <= n; i++) {
                iter[i] = e(i);  // 使用linkList的operator()获取head[i]
            }
            
            // 多路增广
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
};

// 使用示例：
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int n, m;  // n个节点，m条边
    int e;
    int s,t; // 源点 汇点
    std::cin >> n >> m;
    std::cin >> e;
    s = 0;
    t = n + m + 1;
    
    Dinic dinic(n+m+2);  // 创建Dinic实例
    
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        dinic.addEdge(u, v+n, 1);  // 添加有向边
    }

    for(int i = 1;i <= n ;++i ) // i: 1->n
        dinic.addEdge(s, i, 1);

    for(int i = 1;i <= m ;++i ) // i: 1->m
        dinic.addEdge(i+n, t, 1);

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
