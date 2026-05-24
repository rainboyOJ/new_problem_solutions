/**
 * Author by Rainboy
 * Problem: POJ 1041 / OpenJ_Bailian 1041 John's trip
 * Analysis: 
 * 1. 欧拉回路判定：所有点度数为偶数。
 * 2. 字典序最小：邻接表排序 + 贪心 DFS。
 * 3. 算法：Hierholzer 算法 (后序遍历入栈)。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN = 2000; // 街道最大数量 1995
const int MAXM = 50;   // 路口最大编号 44

struct Edge {
    int to;     // 目标路口
    int id;     // 街道编号 (Z)
    
    // 重载小于号，用于排序，保证优先走编号小的边
    bool operator<(const Edge& other) const {
        return id < other.id;
    }
};

// 邻接表：adj[u] 存从 u 出发的所有边
vector<Edge> adj[MAXM];
// 度数数组
int deg[MAXM];
// 标记街道是否被访问过 (根据街道编号 Z 标记)
bool vis[MAXN];
// 结果栈
stack<int> ans;

// 边的总数，当前最大路口编号
int max_street_num;
int max_node_num;

void init() {
    for(int i = 0; i < MAXM; ++i) adj[i].clear();
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));
    max_street_num = 0;
    max_node_num = 0;
}

// Hierholzer 算法核心 DFS
void dfs(int u) {
    // 遍历 u 的所有出边
    // 注意：这里不能用简单的 for(int i=0...) 索引遍历
    // 因为边会动态被标记 visited，我们需要找“下一条可用的边”
    // 在实际实现中，为了效率，通常不删除 vector 元素，而是检查 vis 标记
    for (int i = 0; i < adj[u].size(); ++i) {
        int edge_id = adj[u][i].id;
        int v = adj[u][i].to;

        // 如果这条街没走过
        if (!vis[edge_id]) {
            vis[edge_id] = true; // 标记这条街已走
            dfs(v);              // 递归走向下一个路口
            
            // 【关键】回溯时入栈
            // 此时记录的是 edge_id
            ans.push(edge_id);
        }
    }
}

int main() {
    int x, y, z;
    while (cin >> x >> y) {
        if (x == 0 && y == 0) break;
        
        init();
        cin >> z;
        
        // 读取第一条边，以此确定起点
        // 题目说：住在输入中第一个出现的...所连接的路口
        // 通常理解为：Edge 1 连接的 min(u, v) 或者直接就是输入的第一个 x, y
        // 本题为了字典序最小，且起点未明确固定，通常取整个图中 最小街道编号 所连接的 编号较小的路口
        // 但根据题意 "John lives at ... input first ... street", 我们记录起始边的信息
        int start_node = min(x, y); 
        
        // 记录第一条边
        max_node_num = max(max_node_num, max(x, y));
        deg[x]++; deg[y]++;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
        
        // 继续读取直到遇到 0 0 (本题是一个数据块以 0 0 结束输入，不是整个程序)
        // 修正：POJ 1041 的输入格式是每行 x y z，直到 x=0 y=0 结束一个 Case
        // 所以上面的 while 需要调整为处理 block
        
        // 重新组织输入逻辑：
        // 此时已经读了第一行 x, y, z
        while (true) {
            int u, v, w;
            cin >> u >> v;
            if (u == 0 && v == 0) break; // 当前 Case 结束
            cin >> w;
            
            deg[u]++; deg[v]++;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            max_node_num = max(max_node_num, max(u, v));
        }
        
        // 1. 检查度数 (欧拉回路判定)
        bool possible = true;
        for (int i = 1; i <= max_node_num; ++i) {
            if (deg[i] % 2 != 0) {
                possible = false;
                break;
            }
        }
        
        if (!possible) {
            cout << "Round trip does not exist." << endl;
            continue;
        }
        
        // 2. 对邻接表进行排序，保证字典序最小
        for (int i = 1; i <= max_node_num; ++i) {
            sort(adj[i].begin(), adj[i].end());
        }
        
        // 3. 执行 Hierholzer DFS
        // 起点选择：题目中暗示起点是输入的第一条街道连接的较小路口
        // 实际上，为了字典序最小，我们通常从输入的第一条边涉及的节点开始
        dfs(start_node);
        
        // 4. 输出结果
        // Hierholzer 算法得到的栈是逆序的路径，出栈即为正序
        // 但注意：我们是在 dfs(v) 之后 push 的
        // 比如 1->2, 递归2, 2无路，push(1-2的id)。
        // 最后的路径是 栈顶 -> 栈底
        while (!ans.empty()) {
            cout << ans.top() << (ans.size() == 1 ? "" : " ");
            ans.pop();
        }
        cout << endl;
    }
    return 0;
}
