/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-22 18:20
 * update_at: 2026-10-22 18:20
 */
// P1262 [POI 1996 R3] 间谍网络
//
// 建模：间谍是点，A 掌握 B 的证据是从 A 到 B 的有向边，「控制」就是沿边可达。
// 一旦买下某人，他的整条下游都免费到手，所以真正要决策的只是「从哪些点进入」。
// 互相可达的一批人（强连通分量）里买最便宜的即可，缩点后得到 DAG；
// DAG 中每个点都能上溯到某个入度为 0 的分量，那些分量无人能揭发、只能直接收买。
// 于是答案 = 每个入度为 0 的分量内最便宜的可收买价之和。
//
// 强连通分量用 rbook 的 Tarjan 模板（book/code/graph/scc.cpp）。
// n <= 3000，递归深度最多 3000，栈空间安全，按模板直接递归。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3005;
const int maxe = 8005;
const int INF = 1e9;  // 贿赂价上限 20000，INF 不会与任何真实价格相撞

// 链式前向星，与 linklist.cpp 同结构：Tarjan 模板里的 e.h / e[i].next 都由它提供。
struct linkList {
    typedef struct { int u, v, w, next; } edge;
    edge e[maxe];
    int h[maxn], edge_cnt = 0;
    linkList() { reset(); }

    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }
    void add(int u, int v, int w = 0) {
        e[edge_cnt] = {u, v, w, h[u]};
        h[u] = edge_cnt++;
    }
    edge& operator[](int i) { return e[i]; }
} e;

struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt;  // SCC 的总数

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
    }

    // 有向图,不要加father参数
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e.h[u]; ~i ; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {  // 如果 v 没被访问过
                dfs(v);

                // 根据子节点的 low 值更新当前节点的 low 值
                low[u] = std::min(low[u], low[v]);
            } else if (in_stack[v]) {  // 返祖边, 如果 v 在栈中，说明构成了环
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        // 如果 dfn == low，说明找到了一个 SCC 的起始点
        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (1) {
                int v = st.top(); st.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt;  // 标记所属 SCC 编号
                if (v == u) break;    // 直到找到起始点
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
} scc;

int n, p, r;

int cost[maxn];      // cost[v] = 收买 v 的价格，INF 表示不可收买
int min_cost[maxn];  // min_cost[c] = 分量 c 内最便宜的可收买价
int indeg[maxn];     // 缩点后分量 c 的入度，只统计跨分量的边
bool reach[maxn];    // 从所有可收买点出发能否到达

void read_input() {
    cin >> n;
    cin >> p;
    fill(cost, cost + n + 1, INF);
    for (int i = 0; i < p; i++) {
        int v, c;
        cin >> v >> c;
        cost[v] = c;
    }
    cin >> r;
    for (int i = 0; i < r; i++) {
        int u, v;
        cin >> u >> v;
        e.add(u, v);
    }
}

void solve() {
    scc.set(n);
    scc.solve();
    int cnt = scc.scc_cnt;

    fill(min_cost, min_cost + cnt + 1, INF);
    for (int v = 1; v <= n; v++) {
        int c = scc.scc_id[v];
        min_cost[c] = min(min_cost[c], cost[v]);
    }

    // 缩点后 DAG 的入度：环内的边不算，否则环上的分量入度都被自己凑成非 0
    for (int u = 1; u <= n; u++) {
        for (int i = e.h[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (scc.scc_id[u] != scc.scc_id[v]) indeg[scc.scc_id[v]]++;
        }
    }

    // 买下所有可收买者能控制的范围：买得越多只会更广，所以全买就是最大可达集。
    // 谁都不在其中，就永远无法控制。
    {
        std::queue<int> q;
        for (int v = 1; v <= n; v++) {
            if (cost[v] < INF) {
                reach[v] = true;
                q.push(v);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = e.h[u]; ~i; i = e[i].next) {
                int v = e[i].v;
                if (!reach[v]) {
                    reach[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // 注意：这里要找「所有不可达点里编号最小的」，不是「坏分量里编号最小的」。
    // 坏分量的下游同样失控，而那些点的编号可能更小。
    int bad = 0;
    for (int v = 1; v <= n; v++) {
        if (!reach[v]) { bad = v; break; }
    }
    if (bad) {
        cout << "NO\n" << bad << "\n";
        return;
    }

    long long total = 0;  // 最坏 3000 * 20000 = 6e7，int 够，统一用 long long
    for (int c = 1; c <= cnt; c++) {
        if (indeg[c] == 0) total += min_cost[c];
    }
    cout << "YES\n" << total << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
