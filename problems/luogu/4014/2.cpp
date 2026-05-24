/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-12
 * Problem: P4014 分配问题
 * Algorithm: Min-Cost Max-Flow (MCMF)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e4+5; 
const int maxe = 1e5+5; 
const long long INF = 1e18;
const int INF_INT = 0x3f3f3f3f;

int n;
int s, t; // 源点 汇点
int costs[105][105]; // 存储输入的效益矩阵

// --- 存图模板 (保持你的风格) ---

struct linkList {
    typedef struct {int u,v,w,c,next;} edge; 
    edge e[maxe];
    int h[maxn], edge_cnt=0;
    
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    void add(int u, int v, int w=0, int c=0){
        e[edge_cnt] = {u, v, w, c, h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }
} e;

// --- MCMF 算法模板 ---

struct MCMF {
    int dis[maxn];   
    int flow[maxn];  
    int pre[maxn];   
    int last[maxn];  
    bool vis[maxn];  
    int n;           
    
    long long max_flow;
    long long min_cost;

    void init(int n) {
        e.reset();
        this->n = n;
    }
    
    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);      // 正向边
        e.add(v, u, 0, -cost);       // 反向边
    }
    
    bool spfa(int s, int t) {
        for(int i = 0; i <= n+1; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        
        queue<int> q;
        dis[s] = 0;
        vis[s] = 1;
        pre[t] = -1; 
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v;
                int cap = e[i].w;
                int cost = e[i].c;

                if (cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;
                    pre[v] = u;    
                    last[v] = i;   
                    flow[v] = min(flow[u], cap);
                    
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return pre[t] != -1;
    }
    
    void solve(int s, int t) {
        max_flow = 0;
        min_cost = 0;
        
        while (spfa(s, t)) {
            int now = t;
            int f = flow[t]; 
            
            max_flow += f;
            min_cost += (long long)f * dis[t];
            
            while (now != s) {
                int edge_idx = last[now]; 
                e[edge_idx].w -= f;       
                e[edge_idx ^ 1].w += f;   
                now = pre[now]; 
            }
        }
    }
} mcmf;

// --- 针对 P4014 分配问题的逻辑 ---

// mode = 1: 求最小效益 (cost = c_ij)
// mode = 2: 求最大效益 (cost = -c_ij)
long long build_and_solve(int mode) {
    // 节点规划:
    // S = 0
    // 人 = 1 ~ n
    // 工作 = n+1 ~ 2n
    // T = 2n + 1
    
    s = 0;
    t = 2 * n + 1;
    
    // 初始化 MCMF
    mcmf.init(t);

    for (int i = 1; i <= n; i++) {
        // 1. 源点 -> 人 (容量1, 费用0)
        mcmf.addEdge(s, i, 1, 0);

        // 2. 工作 -> 汇点 (容量1, 费用0)
        // 工作的节点编号偏移了 n，即 i+n
        mcmf.addEdge(i + n, t, 1, 0);

        for (int j = 1; j <= n; j++) {
            // 3. 人 -> 工作 (容量1, 费用由 mode 决定)
            int cost = costs[i][j];
            if (mode == 2) cost = -cost; // 求最大值时取反
            
            mcmf.addEdge(i, j + n, 1, cost);
        }
    }

    mcmf.solve(s, t);
    
    if (mode == 2) return -mcmf.min_cost; // 最大值记得取反回来
    return mcmf.min_cost;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    
    // 读入矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> costs[i][j];
        }
    }
    
    // 第一行输出最小总效益
    cout << build_and_solve(1) << endl;
    
    // 第二行输出最大总效益
    cout << build_and_solve(2) << endl;
    
    return 0;
}
