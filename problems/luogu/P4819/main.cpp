/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 12:51
 * update_at: 2026-10-30 17:50
 */
// P4819 [中山市选] 杀人游戏
// Tarjan 缩点 + DAG 入度统计 + 排除法特例（O(N+M) 正确解法）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;

int n, m;
vector<int> g[MAXN];           // 有向图邻接表

// Tarjan 缩点
int dfn[MAXN], low[MAXN], timer;
int scc[MAXN], scc_cnt, sz[MAXN];
bool in_stack[MAXN];
vector<int> stk;               // Tarjan 的顶点栈（不是 DFS 调用栈）

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push_back(u);
    in_stack[u] = true;

    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    // u 是所在 SCC 的根，弹出整个 SCC
    if (dfn[u] == low[u]) {
        scc_cnt++;
        sz[scc_cnt] = 0;
        while (true) {
            int y = stk.back();
            stk.pop_back();
            in_stack[y] = false;
            scc[y] = scc_cnt;
            sz[scc_cnt]++;
            if (y == u) break;
        }
    }
}

// 缩点后的 DAG
vector<int> dag[MAXN];
int in_deg[MAXN];

// 由 SCC 缩点建 DAG（邻接表去重）
void build_dag() {
    vector<set<int>> temp(scc_cnt + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (scc[u] != scc[v]) {
                temp[scc[u]].insert(scc[v]);
            }
        }
    }
    for (int i = 1; i <= scc_cnt; i++) {
        dag[i].clear();
        for (int v : temp[i]) {
            dag[i].push_back(v);
        }
    }
}

// 统计 DAG 上每个 SCC 的入度
void calc_in_deg() {
    memset(in_deg, 0, sizeof(int) * (scc_cnt + 1));
    for (int i = 1; i <= scc_cnt; i++) {
        for (int v : dag[i]) {
            in_deg[v]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);       // 有向边：x 认识 y
    }

    // Tarjan 缩点
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }

    // 缩点建 DAG，统计入度
    build_dag();
    calc_in_deg();

    // 统计入度为 0 的 SCC 数量
    int cnt = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_deg[i] == 0) cnt++;
    }

    // 排除法特例：size==1 且入度 0 的 SCC，其所有后继入度 ≥2 即可省略
    // 这是 O(1) 检查，不需要 BFS
    bool can_omit = false;
    for (int i = 1; i <= scc_cnt && !can_omit; i++) {
        if (in_deg[i] == 0 && sz[i] == 1) {
            bool ok = true;
            for (int v : dag[i]) {
                if (in_deg[v] <= 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) can_omit = true;
        }
    }

    // 必须冒险询问的次数
    // 特例：n==1 时不需要任何询问
    int must = (n == 1 ? 0 : cnt);
    if (can_omit && must > 0) must = must - 1;

    // 幸存且确定杀手的概率
    double ans = 1.0 - (double)must / n;
    printf("%.6f\n", ans);

    return 0;
}
