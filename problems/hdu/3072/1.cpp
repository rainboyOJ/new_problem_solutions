/**
 * Problem: HDU 1827 - Ultimate Intelligence
 * Analysis: Tarjan SCC + Greedy on DAG
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 50005;   // N <= 50000
const int maxm = 100005;  // M <= 100000
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v, w, next;
} e[maxm];
int head[maxn], e_cnt;

void init_edge() {
    memset(head, -1, sizeof(head));
    e_cnt = 0;
}

void add_edge(int u, int v, int w) {
    e[e_cnt] = {u, v, w, head[u]};
    head[u] = e_cnt++;
}

struct TarjanSolver {
    int dfn[maxn], low[maxn], timer;
    int stack[maxn], top;
    bool in_stack[maxn];
    
    int scc_id[maxn]; // 每个点所属的 SCC 编号
    int scc_cnt;      // SCC 总数

    // 记录进入某个 SCC 的最小花费
    // min_in_cost[i] 表示进入 SCC i 的最小边权
    int min_in_cost[maxn]; 

    void init(int n) {
        timer = scc_cnt = top = 0;
        for(int i = 0; i <= n; i++) {
            dfn[i] = low[i] = 0;
            in_stack[i] = false;
            min_in_cost[i] = INF; // 初始化为无穷大
        }
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++timer;
        stack[++top] = u;
        in_stack[u] = true;

        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            scc_cnt++;
            while (true) {
                int v = stack[top--];
                in_stack[v] = false;
                scc_id[v] = scc_cnt;
                if (u == v) break;
            }
        }
    }

    void solve(int n, int m) {
        // 1. 求 SCC
        for(int i = 0; i < n; i++) {
            if(!dfn[i]) tarjan(i);
        }

        // 2. 遍历所有边，计算每个 SCC 的最小入边花费
        int start_scc = scc_id[0]; // 起点 0 所在的 SCC

        for(int i = 0; i < m; i++) {
            int u = e[i].u;
            int v = e[i].v;
            int w = e[i].w;

            // 如果这条边连接了两个不同的 SCC
            if(scc_id[u] != scc_id[v]) {
                int target = scc_id[v];
                // 更新进入 target SCC 的最小费用
                if(w < min_in_cost[target]) {
                    min_in_cost[target] = w;
                }
            }
        }

        // 3. 统计答案
        int total_cost = 0;
        for(int i = 1; i <= scc_cnt; i++) {
            // 如果是起点所在的 SCC，不需要花费（本身就有情报）
            if(i == start_scc) continue;
            
            // 累加最小入边花费
            // 题目保证一定有解，所以 min_in_cost[i] 不会是 INF
            total_cost += min_in_cost[i];
        }

        printf("%d\n", total_cost);
    }
} solver;

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        init_edge();
        solver.init(n);

        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
        }

        solver.solve(n, m);
    }
    return 0;
}
