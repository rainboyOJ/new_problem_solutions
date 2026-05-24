/**
 * Problem: HDU 3072 Intelligence System
 * Status: AC
 * Method: Tarjan + SCC缩点 + 贪心
 * Note: 使用 Vector 存图利用缓存局部性，通过 memset 快速初始化
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int N = 50010;
const int INF = 0x3f3f3f3f;

int dfn[N], low[N], bel[N], val[N];
bool instack[N];
vector<int> adj[N], cost[N]; // 使用vector存图
stack<int> st; // 使用STL栈
int scc_cnt, idx, n, m;

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    instack[u] = true;
    st.push(u);
    
    // 遍历所有出边
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 发现强连通分量
    if (dfn[u] == low[u]) {
        int v;
        scc_cnt++;
        do {
            v = st.top();
            st.pop();
            instack[v] = false;
            bel[v] = scc_cnt;
        } while (u != v);
    }
}

int main() {
    // 关闭同步流，加速 cin/cout
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> n >> m) {
        // 1. 初始化
        // 对于大数据量的多组测试，memset 通常比手动循环赋值更加底层优化
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(bel, 0, sizeof(bel));
        memset(instack, false, sizeof(instack));
        
        // 清空邻接表
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            cost[i].clear();
            val[i] = INF; // 这里的 val 初始化其实在后面会被覆盖，但保持原逻辑
        }
        
        // 清空栈（防止上一组数据残留）
        while (!st.empty()) st.pop();
        scc_cnt = idx = 0;

        // 2. 读入边
        for (int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            adj[u].push_back(v);
            cost[u].push_back(c);
        }

        // 3. Tarjan 缩点
        for (int i = 0; i < n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }

        // 4. 初始化每个 SCC 的最小入边权值
        for (int i = 1; i <= scc_cnt; i++) {
            val[i] = INF;
        }

        // 5. 遍历所有边，计算缩点后的最小入边
        for (int u = 0; u < n; u++) {
            for (int j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j];
                int scc_u = bel[u];
                int scc_v = bel[v];
                
                // 如果边连接两个不同的 SCC，更新目标 SCC 的最小入边花费
                if (scc_u != scc_v) {
                    val[scc_v] = min(val[scc_v], cost[u][j]);
                }
            }
        }

        // 6. 计算总成本
        int ans = 0;
        for (int i = 1; i <= scc_cnt; i++) {
            // 关键逻辑：排除包含节点0（起点）的SCC，因为它不需要被通知（它是消息源）
            // 并且过滤掉不可达的INF（虽然题目保证连通，但加上保险）
            if (i != bel[0] && val[i] != INF) { 
                ans += val[i];
            }
        }
        
        cout << ans << endl;
    }
    return 0;
}

