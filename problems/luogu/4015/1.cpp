#include <bits/stdc++.h>
using namespace std;

// 调整了数组大小以适应 N, M <= 100 的情况，虽然原大小也没问题
const int maxn = 1e5 + 5; 
const int maxe = 2e5 + 5; 
const long long INF = 1e18;
const int INF_INT = 0x3f3f3f3f;

int n, m; // n: 商店数, m: 仓库数 (题目定义)
int s, t; // 源点 汇点

// 为了能跑两遍（最小和最大），我们需要先保存输入数据
int a[205]; // 仓库货物量
int b[205]; // 商店需求量
int c[205][205]; // 费用矩阵

// 存图的模板 (保持源代码不变)
//oisnip_begin code/graph/linklist.cpp 内容开始
struct linkList {
    typedef struct {int u, v, w, c, next;} edge; 
    edge e[maxe];
    int h[maxn], edge_cnt = 0;
    linkList() { reset(); }

    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }

    void add(int u, int v, int w = 0, int c = 0) {
        e[edge_cnt] = {u, v, w, c, h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i) { return e[i]; }
} e;
//oisnip_end code/graph/linklist.cpp 内容结束

// MCMF 算法模板 (保持源代码不变)
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
        e.reset(); // 每次初始化时清空边
        this->n = n;
    }
    
    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);      
        e.add(v, u, 0, -cost);       
    }
    
    bool spfa(int s, int t) {
        for (int i = 0; i <= n + 1; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        
        queue<int> q;
        dis[s] = 0;
        vis[s] = 1;
        pre[t] = -1; 
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            
            for (int i = e.h[u]; ~i; i = e[i].next) {
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

// 读取输入数据
void read_input() {
    std::cin >> m >> n; // m个仓库，n个商店
    for (int i = 1; i <= m; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> c[i][j];
        }
    }
}

// 构建图
// flag = 1 表示求最小费用（正权边）
// flag = -1 表示求最大费用（费用取反）
void build_graph(int flag) {
    s = 0;
    t = m + n + 1;
    mcmf.init(t + 5); 

    // 1. 源点 -> 仓库 (容量为仓库库存 a[i], 费用 0)
    for (int i = 1; i <= m; ++i) {
        mcmf.addEdge(s, i, a[i], 0);
    }

    // 2. 商店 -> 汇点 (容量为商店需求 b[i], 费用 0)
    for (int i = 1; i <= n; ++i) {
        int id = m + i; // 商店的编号排在仓库之后
        mcmf.addEdge(id, t, b[i], 0);
    }

    // 3. 仓库 -> 商店 (容量无限/INF, 费用为 c[i][j] * flag)
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int id = m + j;
            // 关键点：如果是求最大费用，我们将费用取反
            // MCMF 寻找“最小”负费用，实际上就是寻找“最大”正费用
            mcmf.addEdge(i, id, INF_INT, c[i][j] * flag);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    // 1. 读入数据
    read_input();

    // 2. 第一次求解：最小费用
    build_graph(1); // 正向费用
    mcmf.solve(s, t);
    cout << mcmf.min_cost << "\n";

    // 3. 第二次求解：最大费用
    build_graph(-1); // 费用取反
    mcmf.solve(s, t);
    // 结果是负的最小费用，取反回来就是最大费用
    cout << -mcmf.min_cost << "\n";
    
    return 0;
}
