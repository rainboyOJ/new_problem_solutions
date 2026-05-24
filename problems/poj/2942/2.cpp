// 简化代码
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 1005;

// 存储边的结构体，用于Tarjan栈
struct Edge {
    int u, v;
};

int n, m;
int hate[MAXN][MAXN];       // 邻接矩阵存"讨厌"关系
vector<int> G[MAXN];        // 邻接表存补图（兼容关系）
int dfn[MAXN], low[MAXN], dfs_clock;
stack<Edge> stk;            // 存边的栈
int bcc_cnt;
vector<int> bcc_nodes[MAXN]; // 存每个BCC包含的点列表
int color[MAXN];             // 染色数组 (0:未染, 1:黑, 2:白)
bool able[MAXN];             // 最终标记：该骑士是否能上桌
int node_marker[MAXN];       // 辅助数组，用于标记节点属于当前BCC

// 初始化函数，多组数据必备
void init() {
    memset(hate, 0, sizeof(hate));
    for (int i = 1; i <= n; i++) G[i].clear();
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(able, 0, sizeof(able));
    memset(node_marker, 0, sizeof(node_marker));
    dfs_clock = 0;
    bcc_cnt = 0;
    while (!stk.empty()) stk.pop();
}

// 判定一个具体的 BCC 是否为二分图
// id: BCC的编号
bool check_bipartite(int id) {
    // 1. 准备工作：将该BCC内的点标记一下，方便后续只在BCC内部走
    // 同时重置颜色
    for (int u : bcc_nodes[id]) {
        color[u] = 0;
        node_marker[u] = id; 
    }
    
    // 2. 染色 BFS/DFS
    // 即使在BCC内部，染色也要遍历所有点（防止BCC本身不连通？
    // 其实BCC定义上是连通的，但为了代码健壮性，通常只需从第一个点开始）
    if (bcc_nodes[id].empty()) return true;
    
    // 用队列进行BFS染色
    vector<int> q;
    q.push_back(bcc_nodes[id][0]);
    color[bcc_nodes[id][0]] = 1;
    
    int head = 0;
    while(head < q.size()){
        int u = q[head++];
        for(int v : G[u]){
            // 关键：只走属于当前BCC的点
            if(node_marker[v] != id) continue;
            
            if(color[v] == 0){
                color[v] = 3 - color[u]; // 1变2，2变1
                q.push_back(v);
            } else if(color[v] == color[u]){
                return false; // 发现冲突，不是二分图 -> 有奇环
            }
        }
    }
    return true; // 没有冲突 -> 是二分图 -> 无奇环
}

// Tarjan求点双连通分量
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++dfs_clock;
    for (int v : G[u]) {
        if (v == fa) continue;
        
        if (!dfn[v]) {
            stk.push({u, v}); // 存边
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            
            if (low[v] >= dfn[u]) { // 割点判定条件
                bcc_cnt++;
                bcc_nodes[bcc_cnt].clear();
                
                while (true) {
                    Edge e = stk.top();
                    stk.pop();
                    // 将边的两端加入点集
                    if(node_marker[e.u] != bcc_cnt) {
                        bcc_nodes[bcc_cnt].push_back(e.u);
                        node_marker[e.u] = bcc_cnt;
                    }
                    if(node_marker[e.v] != bcc_cnt) {
                        bcc_nodes[bcc_cnt].push_back(e.v);
                        node_marker[e.v] = bcc_cnt;
                    }
                    if (e.u == u && e.v == v) break;
                }
                
                // 立即对该BCC进行审判
                // 如果不是二分图（有奇环），则该BCC所有人都复活
                if (!check_bipartite(bcc_cnt)) {
                    for (int k : bcc_nodes[bcc_cnt]) {
                        able[k] = true;
                    }
                }
            }
        } else if (dfn[v] < dfn[u]) {
            stk.push({u, v});
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) && (n || m)) {
        init();
        
        // 读入讨厌关系
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            hate[u][v] = hate[v][u] = 1;
        }
        
        // 构建补图
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!hate[i][j]) {
                    G[i].push_back(j);
                    G[j].push_back(i);
                }
            }
        }
        
        // 遍历全图（防止原图不连通）
        // 这里重置node_marker用于Tarjan过程中的临时去重
        memset(node_marker, 0, sizeof(node_marker)); 
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) tarjan(i, -1);
        }
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (!able[i]) ans++;
        }
        
        printf("%d\n", ans);
    }
    return 0;
}
