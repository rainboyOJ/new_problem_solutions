/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-31 22:21:06
 * Modified for Min-Cost Max-Flow
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边 (注意：要是题目边数的2倍)
const long long INF = 1e18;
const int INF_INT = 0x3f3f3f3f;

int n,m;
int s,t; // 源点 汇点

// 坐标映射
int val[45][45];
int node_id[45][45];

// 存图的模板

//oisnip_begin code/graph/linklist.cpp 内容开始

struct linkList {
    // 修改点1: 增加 c (cost) 字段
    typedef struct {int u,v,w,c,next;} edge; 
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    // 修改点2: add 增加 cost 参数
    void add(int u,int v,int w=0, int c=0){
        e[edge_cnt] = {u,v,w,c,h[u]};
        h[u] = edge_cnt++;
    }
    
    //下标访问
    edge& operator[](int i){ return e[i]; }
} e;

//oisnip_end code/graph/linklist.cpp 内容结束


// MCMF 算法模板 - 基于linkList存图
// 最小费用最大流
struct MCMF {
    int dis[maxn];   // SPFA 最短路（最小费用）
    int flow[maxn];  // 到达当前节点的最小流量限制
    int pre[maxn];   // 记录路径：前驱节点
    int last[maxn];  // 记录路径：前驱边
    bool vis[maxn];  // SPFA 队列标记
    int n;           // 节点数
    
    long long max_flow;
    long long min_cost;

    void init(int n) {
        // 重置linkList
        e.reset();
        this->n = n;
    }
    
    // 添加边：从u到v，容量为cap，单位费用为cost
    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);      // 正向边：容量cap，费用cost
        e.add(v, u, 0, -cost);       // 反向边：容量0，费用-cost
    }
    
    // SPFA 寻找单位费用最小的增广路
    // 返回是否能到达汇点
    bool spfa(int s, int t) {
        // 初始化
        for(int i = 0; i <= n+1; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        
        queue<int> q;
        dis[s] = 0;
        vis[s] = 1;
        pre[t] = -1; // 标记汇点前驱，用于判断是否可达
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            
            // 使用linkList的遍历方式
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v;
                int cap = e[i].w;
                int cost = e[i].c;

                // 如果有残余容量 且 路径费用更小
                if (cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;
                    pre[v] = u;    // 记录前驱节点
                    last[v] = i;   // 记录前驱边
                    flow[v] = min(flow[u], cap); // 更新路径上的最小流量限制
                    
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        
        return pre[t] != -1;
    }
    
    // 计算 最小费用 & 最大流
    // 结果保存在成员变量 max_flow 和 min_cost 中
    // 也可以修改函数返回 pair<long long, long long>
    void solve(int s, int t) {
        max_flow = 0;
        min_cost = 0;
        
        // 只要还能找到费用最小的路径（SPFA），就继续增广
        while (spfa(s, t)) {
            int now = t;
            int f = flow[t]; // 本次增广的流量
            
            max_flow += f;
            min_cost += (long long)f * dis[t];
            
            // 回溯更新残留网络
            while (now != s) {
                int edge_idx = last[now]; // 当前边的下标
                
                e[edge_idx].w -= f;       // 正向边容量减少
                e[edge_idx ^ 1].w += f;   // 反向边容量增加
                
                now = pre[now]; // 向前移动
            }
        }
    }
} mcmf;


int cnt = 0;
void init(){

    cin >> m >> n;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m+i-1; ++j) {
            cin >> val[i][j];
            node_id[i][j] = ++cnt;
        }
}

void solve_rule (int r) {
    int S = 0, T = 2 * cnt + 1;
    mcmf.init(T);
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=m+i-1; ++j) {
            int in = node_id[i][j], out = in + cnt;
            // 内部边：点容量。
            // 规则1：点互不相交 -> cap=1
            // 规则2,3：点可相交 -> cap=INF
            mcmf.addEdge(in, out, (r == 1 ? 1 : INF_INT), -val[i][j]);

            if(i == 1) mcmf.addEdge(S, in, 1, 0); // 顶端起点

            // 连接汇点 T 的逻辑
            // 规则1：终点互不相交 -> cap=1
            // 规则2,3：终点可相交 -> cap=INF
            if(i == n) mcmf.addEdge(out, T, (r == 1 ? 1: INF_INT), 0); // 底端终点

            if(i < n) {
                // 外部边：边容量
                // 规则1,2：边互不相交 -> cap=1
                // 规则3：边可相交 -> cap=INF
                mcmf.addEdge(out, node_id[i+1][j], (r <= 2 ? 1 : INF_INT), 0);
                mcmf.addEdge(out, node_id[i+1][j+1], (r <= 2 ? 1 : INF_INT), 0);
            }
        }
    }
    mcmf.solve(S, T);
    cout << -mcmf.min_cost << endl;
};

// 使用示例：
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();

    
    

    solve_rule(1);
    solve_rule(2);
    solve_rule(3);

    return 0;
}

/*
复杂度分析：
- 时间复杂度：基于SPFA的MCMF算法，复杂度为 O(k * E * F)，其中 F 是最大流，k 是常数（SPFA平均复杂度）。
- 空间复杂度：O(V + E)

使用说明：
1. 创建实例：MCMF mcmf;
2. 初始化：mcmf.init(n);
3. 添加边：mcmf.addEdge(u, v, cap, cost);
4. 求解：mcmf.solve(s, t);
5. 获取结果：mcmf.max_flow 和 mcmf.min_cost

注意事项：
- 节点编号：确保 init(n) 中的 n 覆盖了所有节点编号（建议传 max_node_index）。
- 费用类型：如果费用可能很大，注意 min_cost 使用 long long。
- 负费用：SPFA 可以处理负费用边，但图中不能有负权回路。
*/
