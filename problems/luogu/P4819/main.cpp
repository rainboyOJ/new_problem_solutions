/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 12:51
 * update_at: 2026-10-23 13:20
 */
// P4819 [中山市选] 杀人游戏
// Tarjan 缩点 + DAG 入度统计 + 排除法特例
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXM = 300010 * 2; // 双向预留

int n, m;

// 链式前向星
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// Tarjan 变量
int dfn[MAXN], low[MAXN], timer;
int scc[MAXN], scc_cnt, sz[MAXN];
bool in_stack[MAXN];
vector<int> stk;

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push_back(u);
    in_stack[u] = true;

    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (dfn[v] == 0) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stack[v]) {
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }

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

void build_dag() {
    // 使用 vector<unordered_set> 或简单 vector 后去重
    // 这里用 vector<int> + 排序去重，或用 set 临时
    vector<set<int>> temp(scc_cnt + 1);
    for (int u = 1; u <= n; u++) {
        int su = scc[u];
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            int sv = scc[v];
            if (su != sv) {
                temp[su].insert(sv);
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
        add_edge(x, y);
    }

    // Tarjan
    timer = 0;
    scc_cnt = 0;
    stk.clear();
    memset(dfn, 0, sizeof(int) * (n + 1));
    memset(low, 0, sizeof(int) * (n + 1));
    memset(scc, 0, sizeof(int) * (n + 1));
    memset(in_stack, 0, sizeof(bool) * (n + 1));

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }

    // 缩点建 DAG
    build_dag();
    calc_in_deg();

    // 统计入度为 0 的 SCC 数量
    int cnt = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_deg[i] == 0) cnt++;
    }

    // 准确判断是否可省略：使用可达性检查
    // 对于每个 size==1 的入度0 SCC s，模拟从其他入度0出发的达到，
    // 若未覆盖的原图节点数 == 1，则可省略询闩 s
    auto can_omit_accurate = [&](int omit_s) -> bool {
        if (sz[omit_s] != 1) return false;
        // 多源 BFS on condensed DAG
        vector<bool> vis(scc_cnt + 1, false);
        vector<int> q;
        for (int i = 1; i <= scc_cnt; i++) {
            if (in_deg[i] == 0 && i != omit_s) {
                if (!vis[i]) {
                    vis[i] = true;
                    q.push_back(i);
                }
            }
        }
        size_t head = 0;
        while (head < q.size()) {
            int u = q[head++];
            for (int v : dag[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push_back(v);
                }
            }
        }
        int covered = 0;
        for (int node = 1; node <= n; node++) {
            if (vis[ scc[node] ]) covered++;
        }
        int unknown = n - covered;
        return unknown == 1;
    };

    bool can_omit = false;
    for (int i = 1; i <= scc_cnt && !can_omit; i++) {
        if (in_deg[i] == 0 && can_omit_accurate(i)) {
            can_omit = true;
        }
    }

    int must = cnt;
    if (can_omit) {
        must = cnt - 1;
    }
    if (must < 0) must = 0;

    double ans = 1.0 - (double)must / n;
    printf("%.6f\n", ans);

    return 0;
}
