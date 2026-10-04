/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:30
 * update_at: 2026-10-05 05:43
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 10005;

typedef long long ll;

// n 个学校，m 条支援关系
ll n, m;

// 链式前向星存图
int head[MAXN], nxt[MAXM], to[MAXM], edge_cnt;

// Tarjan 所需：dfn 时间戳、low 追溯值、栈内标记、栈、分量编号
int dfn[MAXN], low[MAXN], stk[MAXN];
bool in_stk[MAXN];
int timer_cnt, top_cnt, scc_cnt;
int scc_id[MAXN]; // scc_id[u] 表示节点 u 所属的强连通分量编号

// 缩点后 DAG 中每个分量的入度与出度
int in_deg[MAXN], out_deg[MAXN];

// 加一条 u -> v 的有向边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// Tarjan 求强连通分量。
void tarjan(int u) {
    timer_cnt++;
    dfn[u] = low[u] = timer_cnt;
    top_cnt++;
    stk[top_cnt] = u;
    in_stk[u] = true;

    for (int i = head[u]; i != 0; i = nxt[i]) {
        int v = to[i];
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    // u 是当前强连通分量的根，弹出整个分量并编号
    if (low[u] == dfn[u]) {
        scc_cnt++;
        while (true) {
            int v = stk[top_cnt];
            top_cnt--;
            in_stk[v] = false;
            scc_id[v] = scc_cnt;
            if (v == u) break;
        }
    }
}

void read_input() {
    cin >> n;
    m = 0;
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        int v;
        while (cin >> v && v != 0) {
            add_edge(i, v);
            m++;
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) tarjan(i);
    }

    // 统计缩点后 DAG 中每个分量的入度与出度（只算跨分量的边）
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (scc_id[u] != scc_id[v]) {
                out_deg[scc_id[u]]++;
                in_deg[scc_id[v]]++;
            }
        }
    }

    // P 为入度为 0 的分量数，Q 为出度为 0 的分量数
    int p = 0, q = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in_deg[i] == 0) p++;
        if (out_deg[i] == 0) q++;
    }

    // 任务 A：给所有入度为 0 的分量发软件即可覆盖全图
    cout << p << "\n";
    // 任务 B：整个图已强连通时不用加边，否则答案是 max(P, Q)
    if (scc_cnt == 1)
        cout << 0 << "\n";
    else
        cout << max(p, q) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
