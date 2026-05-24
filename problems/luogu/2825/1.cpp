/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-12 19:34:42
 * Problem: P2825 [HEOI2016/TJOI2016] 游戏
 * Algorithm: Max Flow (Dinic) / Bipartite Matching
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边
const long long INF = 1e18;

int n, m;
int s, t; // 源点 汇点
char grid[60][60];      // 存储地图
int row_id[60][60];     // 记录每个格子属于哪个“行块”
int col_id[60][60];     // 记录每个格子属于哪个“列块”

// --- 存图模板 (你的模板保持不变) ---
//oisnip_begin code/graph/linklist.cpp 内容开始
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
} e;
//oisnip_end code/graph/linklist.cpp 内容结束


// --- Dinic算法模板 (你的模板保持不变) ---
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
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边
        e.add(v, u, 0);      // 反向边
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
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; // 当前弧优化
            int to = edge.v;
            long long cap = edge.w;
            
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            long long tr = dfs(to, t, min(preFlow, cap));

            e[cid].w -= tr ;     // 正向边容量减少
            e[cid ^ 1].w += tr;  // 反向边容量增加
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    // 求从s到t的最大流
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {  // 能够分层
            for (int i = 0; i <= n; i++) {
                cur[i] = e.h[i];
            }
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// --- 针对 P2825 的初始化逻辑 ---
void init(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // 1. 处理“行块” ID
    // 遇到硬石头 #，或者换行时，ID增加（产生新的块）
    int tot_row = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (grid[i][j] == '#') continue; // 硬石头不属于任何块
            
            // 如果是该行的第一个，或者前一个是硬石头，说明新起了一个块
            if (j == 0 || grid[i][j-1] == '#') {
                tot_row++;
            }
            row_id[i][j] = tot_row;
        }
    }

    // 2. 处理“列块” ID
    // 逻辑同上，只是外层循环是列，内层是行
    int tot_col = 0;
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            if (grid[i][j] == '#') continue;

            if (i == 0 || grid[i-1][j] == '#') {
                tot_col++;
            }
            col_id[i][j] = tot_col;
        }
    }

    // 3. 建图
    // S = 0
    // 行块节点 = 1 ~ tot_row
    // 列块节点 = tot_row + 1 ~ tot_row + tot_col
    // T = tot_row + tot_col + 1
    
    s = 0;
    t = tot_row + tot_col + 1;
    dinic.init(t + 5);

    // 源点 -> 所有行块 (容量1)
    for(int i = 1; i <= tot_row; i++) {
        dinic.addEdge(s, i, 1);
    }

    // 所有列块 -> 汇点 (容量1)
    for(int i = 1; i <= tot_col; i++) {
        dinic.addEdge(tot_row + i, t, 1);
    }

    // 行块 -> 列块
    // 遍历每一个格子，如果是空地 *，则可以在这里放炸弹
    // 这意味着占用了它所属的行块和列块
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                int u = row_id[i][j];           // 当前格子所属行块
                int v = tot_row + col_id[i][j]; // 当前格子所属列块 (加上偏移量)
                dinic.addEdge(u, v, 1);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    
    cout << dinic.maxFlow(s, t) << "\n";
    
    return 0;
}
