/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:20
 * update_at: 2026-10-23 23:20
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 80005;
const int MAXM = 200005;

// 原图与缩点后图的链式前向星
int head[MAXN], edge_cnt;
struct Edge {
    int to;
    int next;
    ll w;
    int coef; // 衰减系数 * 10
} edges[MAXM];

void add_edge(int u, int v, ll w, int coef) {
    edge_cnt++;
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].w = w;
    edges[edge_cnt].coef = coef;
    head[u] = edge_cnt;
}

// 原始输入的边，供缩点后重构图使用
struct RawEdge {
    int u, v;
    ll w;
    int coef;
} raw_edges[MAXM];

// Tarjan 缩点相关变量
int dfn[MAXN], low[MAXN], timer;
int stk[MAXN], top;
bool in_stack[MAXN];
int scc[MAXN], scc_cnt;
ll scc_weight[MAXN]; // 每个强连通分量内部所有边的全收益之和

// 计算一条边反复经过直至为 0 的总蘑菇数
ll calc_all_gain(ll w, int coef) {
    ll sum = 0;
    while (w > 0) {
        sum += w;
        w = (w * coef) / 10;
    }
    return sum;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;
    in_stack[u] = true;

    for (int e = head[u]; e; e = edges[e].next) {
        int v = edges[e].to;
        if (!dfn[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stack[v]) {
            if (dfn[v] < low[u]) low[u] = dfn[v];
        }
    }

    if (low[u] == dfn[u]) {
        scc_cnt++;
        while (true) {
            int node = stk[top--];
            in_stack[node] = false;
            scc[node] = scc_cnt;
            if (node == u) break;
        }
    }
}

// 缩点后 DAG 的链式前向星
int dag_head[MAXN], dag_edge_cnt;
struct DagEdge {
    int to;
    int next;
    ll w;
} dag_edges[MAXM];

int in_degree[MAXN];

void add_dag_edge(int u, int v, ll w) {
    dag_edge_cnt++;
    dag_edges[dag_edge_cnt].to = v;
    dag_edges[dag_edge_cnt].next = dag_head[u];
    dag_edges[dag_edge_cnt].w = w;
    dag_head[u] = dag_edge_cnt;
    in_degree[v]++;
}

// DAG 拓扑排序求最长路
ll dist[MAXN];
int q[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= m; ++i) {
        int u, v;
        ll w;
        double c;
        cin >> u >> v >> w >> c;
        int coef = (int)round(c * 10);
        raw_edges[i] = {u, v, w, coef};
        add_edge(u, v, w, coef);
    }

    int start_node;
    cin >> start_node;

    // 运行 Tarjan 缩点
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // 统计强连通分量内部边的贡献，并建立 DAG 边
    for (int i = 1; i <= m; ++i) {
        int u = raw_edges[i].u;
        int v = raw_edges[i].v;
        int su = scc[u];
        int sv = scc[v];
        if (su == sv) {
            scc_weight[su] += calc_all_gain(raw_edges[i].w, raw_edges[i].coef);
        } else {
            // 跨分量的单向边，只能采一次（因为 DAG 无法走回路）
            add_dag_edge(su, sv, raw_edges[i].w);
        }
    }

    // 在 DAG 上求从 scc[start_node] 出发的最长路
    int start_scc = scc[start_node];
    for (int i = 1; i <= scc_cnt; ++i) {
        dist[i] = -1; // -1 表示从起点不可达
    }
    dist[start_scc] = scc_weight[start_scc];

    // 拓扑排序
    int front = 0, rear = 0;
    for (int i = 1; i <= scc_cnt; ++i) {
        if (in_degree[i] == 0) {
            q[rear++] = i;
        }
    }

    ll ans = dist[start_scc];

    while (front < rear) {
        int u = q[front++];
        for (int e = dag_head[u]; e; e = dag_edges[e].next) {
            int v = dag_edges[e].to;
            if (dist[u] != -1) {
                ll cand = dist[u] + dag_edges[e].w + scc_weight[v];
                if (cand > dist[v]) {
                    dist[v] = cand;
                }
            }
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q[rear++] = v;
            }
        }
    }

    for (int i = 1; i <= scc_cnt; ++i) {
        if (dist[i] > ans) {
            ans = dist[i];
        }
    }

    cout << ans << "\n";

    return 0;
}
