/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-16 14:46:44
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

// 预估最大球数，N=55时球数大约在1600左右，2005足够
const int MAXN = 3005; 
int n; // 柱子数量

// ------------------- 模板开始 (微调以适应本题逻辑) -------------------
vector<int> adj[MAXN]; // 邻接表：adj[u] 存的是左边点 u 能连到的右边点 v (u < v)
int match[MAXN];       // match[v] = u：表示【右边】的点 v (较大数) 匹配了【左边】的点 u (较小数)
int match_left[MAXN];  // 辅助数组：match_left[u] = v，表示左边点 u 匹配了 v。用于快速找未匹配点和输出
bool vis[MAXN];        // 访问标记

// 添加边：u (小) -> v (大)
void add_edge(int u, int v) {
    adj[u].push_back(v);
}

// DFS 寻找增广路
// u 是左边的点
bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue; 
        vis[v] = true;        

        // 如果 v 没有匹配，或者 v 的匹配对象能找到下家
        if (match[v] == 0 || dfs(match[v])) {
            match[v] = u; // 更新匹配关系：v 的上面是 u
            return true;
        }
    }
    return false; 
}
// ------------------- 模板结束 -------------------

// 判断是否为完全平方数
bool is_sq(int x) {
    int r = sqrt(x);
    return r * r == x;
}

// 记录路径的后继，用于输出
int nxt[MAXN]; 
// 标记是否有前驱，用于找柱子的底座
bool has_prev[MAXN];

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n;

    int ball = 0;      // 当前球的编号
    int max_match = 0; // 当前的最大匹配数
    
    // 增量构建图
    while (true) {
        ball++; // 尝试放入下一个球
        
        // 1. 建边：看旧球 i 能否放在新球 ball 下面 (i -> ball)
        for (int i = 1; i < ball; i++) {
            if (is_sq(i + ball)) {
                add_edge(i, ball);
            }
        }
        
        // 2. 尝试增广
        // 我们只需要看增加这个球后，能否让匹配数+1
        // 增广路必须从一个【当前没有匹配的左部点】开始
        // 为了方便，我们需要维护 match_left 或者每次重算
        
        // 重建 match_left 映射以便快速查找未匹配点
        for(int i=0;i<=ball;i++) match_left[i] = 0;
        for(int v=1; v<=ball; v++) {
            if (match[v] != 0) match_left[match[v]] = v;
        }

        bool found = false;
        // 遍历所有可能的左部点 i
        for (int i = 1; i < ball; i++) {
            // 只有未匹配的点才可能作为增广路的起点
            if (match_left[i] == 0) {
                // 清空访问标记，开始新的一轮寻找
                for(int k=0; k<=ball; k++) vis[k] = 0; 
                
                if (dfs(i)) {
                    max_match++; // 找到一条增广路，匹配数+1
                    found = true;
                    break; // 对于每增加一个球，最多只能增加1个匹配，找到即停
                }
            }
        }
        
        // 3. 检查柱子数量
        // 最小路径覆盖 = 节点总数 - 最大匹配数
        int pillars = ball - max_match;
        
        if (pillars > n) {
            ball--; // 这个球放不下了，回退
            break;
        }
    }
    
    // 输出总球数
    cout << ball << "\n";
    
    // 重构路径用于输出
    // match[v] = u 表示 u -> v
    memset(nxt, 0, sizeof(nxt));
    memset(has_prev, 0, sizeof(has_prev));
    
    for (int v = 1; v <= ball; v++) {
        if (match[v] != 0) {
            int u = match[v];
            nxt[u] = v;
            has_prev[v] = true;
        }
    }
    
    // 打印每根柱子
    for (int i = 1; i <= ball; i++) {
        // 如果 i 没有前驱，说明它是柱子的底
        if (!has_prev[i]) {
            int curr = i;
            while (curr != 0) {
                cout << curr << (nxt[curr] == 0 ? "" : " ");
                curr = nxt[curr];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
