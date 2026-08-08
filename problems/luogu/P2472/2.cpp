#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+5; // 点数足够大
const int maxe = 2e6+5; // 边数足够大

// 存图的模板 
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w);
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }
    int operator()(int u){ return h[u]; }
} e;

// Dinic算法模板 
struct Dinic {
    vector<int> level, iter;
    int n; 
    
    Dinic(int n) : n(n), level(n+5), iter(n+5) {
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));
    }
    
    void addEdge(int u, int v, long long cap) {
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
            
            e.for_each(u, [&](int from, int to, int cap) {
                if (cap > 0 && level[to] < 0) {
                    level[to] = level[u] + 1;
                    q.push(to);
                }
            });
        }
        return level[t] >= 0;
    }
    
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        
        for (int& cid = iter[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid];
            int to = edge.v;
            long long cap = edge.w;
            
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            long long tr = dfs(to, t, min(preFlow, cap));

            e[cid].w -= tr;
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
                iter[i] = e(i);
            }
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
};

// --- P2472 专用逻辑 ---

int R, C, D;
char grid_h[25][25]; // 石柱高度
char grid_l[25][25]; // 蜥蜴位置

// 辅助函数：计算两点距离平方
int distSq(int r1, int c1, int r2, int c2) {
    return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2);
}

// 辅助函数：将二维坐标转换为节点编号
// 每个坐标 (i, j) 拆分为两个点：
// In点编号: (i-1)*C + j
// Out点编号: (i-1)*C + j + (R*C)
int getInId(int r, int c) { return (r - 1) * C + c; }
int getOutId(int r, int c) { return getInId(r, c) + (R * C); }

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    if (!(cin >> R >> C >> D)) return 0;

    int total_nodes = 2 * R * C + 2;
    int s = 0; 
    int t = total_nodes - 1; // 汇点设为最大的编号

    Dinic dinic(total_nodes);

    int lizard_count = 0;

    // 1. 读取石柱高度
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            cin >> grid_h[i][j];
            int h = grid_h[i][j] - '0';
            
            // 如果有石柱 (高度 > 0)
            if (h > 0) {
                // 核心技巧：拆点。 In -> Out，容量为石柱高度
                dinic.addEdge(getInId(i, j), getOutId(i, j), h);

                // 如果这个石柱可以直接跳出边界 (逃生)
                // 距离判断：行 < 1 或 > R，列 < 1 或 > C 的逻辑转换
                // 也就是：如果当前坐标 r <= D 或 r > R - D ...
                // 为什么这样计算: 相当于绘制一个半径为d的圆
                if (i <= D || i > R - D || j <= D || j > C - D) {
                    dinic.addEdge(getOutId(i, j), t, 1e9); // 容量无限
                }
            }
        }
    }

    // 2. 读取蜥蜴位置并构建源点边
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            cin >> grid_l[i][j];
            if (grid_l[i][j] == 'L') {
                lizard_count++;
                // 源点 -> 蜥蜴所在的石柱(In点)，容量 1
                dinic.addEdge(s, getInId(i, j), 1);
            }
        }
    }

    // 3. 构建石柱之间的跳跃边
    // 枚举两个石柱 u 和 v
    for(int r1 = 1; r1 <= R; r1++) {
        for(int c1 = 1; c1 <= C; c1++) {
            if (grid_h[r1][c1] == '0') continue; // 没有石柱不能跳

            for(int r2 = 1; r2 <= R; r2++) {
                for(int c2 = 1; c2 <= C; c2++) {
                    if (r1 == r2 && c1 == c2) continue; // 是同一个点
                    if (grid_h[r2][c2] == '0') continue; // 目标没石柱

                    // 如果距离允许跳跃
                    if (distSq(r1, c1, r2, c2) <= D * D) {
                        // 从 (r1,c1) 的 Out 跳到 (r2,c2) 的 In
                        dinic.addEdge(getOutId(r1, c1), getInId(r2, c2), 1e9);
                    }
                }
            }
        }
    }

    // 4. 计算最大流
    // 最大流 = 能逃跑的最大蜥蜴数量
    long long escaped = dinic.maxFlow(s, t);

    // 题目要求输出：无法逃离的蜥蜴数量
    cout << lizard_count - escaped << "";

    return 0;
}
