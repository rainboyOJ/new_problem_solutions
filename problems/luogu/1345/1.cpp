/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-17 19:29:00
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边 (注意：要是题目边数的2倍)
const long long INF = 1e10; // 无穷大

int n, m; // 这里的 n 是题目中的电脑数
int c1, c2;
int s, t; // 源点 汇点
int a[maxn];

// 存图的模板
// ... (保留你提供的 linkList 代码，未做修改) ...

//oisnip_begin code/graph/linklist.cpp 内容开始
struct linkList {
    typedef struct {int u,v;long long w;int next;} edge;
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

} e;
//oisnip_end code/graph/linklist.cpp 内容结束


// Dinic算法最大流模板 - 基于linkList存图
// ... (保留你提供的 Dinic 代码，未做修改) ...
struct Dinic {
    vector<int> level, cur;  
    int n;  
    
    void init(int n) {
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));
        level.resize(n+5);
        cur.resize(n+5);
        this->n = n;
    }
    
    void addEdge(int u, int v, long long cap) { // 修改cap类型为long long适配INF
        e.add(u, v, cap);    
        e.add(v, u, 0);      
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v;
                long long cap = e[i].w; // 注意类型
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] >= 0;
    }
    
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; 
            int to = edge.v;
            long long cap = edge.w;
            
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            long long tr = dfs(to, t, min(preFlow, cap));

            e[cid].w -= tr ;     
            e[cid ^ 1].w += tr; 
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {  
            for (int i = 0; i <= n; i++) {
                cur[i] = e.h[i];  
            }
            flow += dfs(s, t, INF);
        }
        return flow;
    }
} dinic;

// --- 上面是模板，下面是针对本题的逻辑实现 ---

void init(){
    // 读取输入: N个电脑, M条连接, C1和C2是需要阻断的两台电脑
    std::cin >> n >> m >> c1 >> c2;

    // 拆点逻辑：
    // 每个点 i 拆分为：入点 i， 出点 i + n
    // 最大节点编号变为 2 * n
    // Dinic 初始化需要覆盖到所有节点
    dinic.init(2 * n + 5);
    
    // 1. 构建点内部的边 (拆点)
    for (int i = 1; i <= n; i++) {
        int u_in = i;
        int u_out = i + n;
        
        long long cap = 1; // 默认破坏一个电脑的代价是 1
        
        // 题目要求：c1 和 c2 不能被破坏
        if (i == c1 || i == c2) {
            cap = INF;
        }
        
        // 添加入点到出点的边
        dinic.addEdge(u_in, u_out, cap);
    }

    // 2. 构建原来的连接 (线路)
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // 线路是无向的，且线路不会坏（容量INF）
        // 信号流向：u出 -> v入， v出 -> u入
        dinic.addEdge(u + n, v, INF);
        dinic.addEdge(v + n, u, INF);
    }

    // 设置源点和汇点
    // 源点：C1 的入点 (C1 本身)
    // 汇点：C2 的出点 (C2 + N)
    s = c1;
    t = c2 + n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    init(); // 建图
    
    // 跑最大流得到最小割
    cout << dinic.maxFlow(s, t) << "\n";
    
    return 0;
}

