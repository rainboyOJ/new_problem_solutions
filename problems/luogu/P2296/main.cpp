#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000 + 5;
const int MAXM = 200000 + 5;

int n, m;
int s, t;

int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int rhead[MAXN], rto[MAXM], rnxt[MAXM], redge_cnt;
int out_deg[MAXN];

bool can_reach_t[MAXN]; // 在原图中，这个点能否走到终点 t
bool safe_node[MAXN];   // 这个点的所有出边是否都指向 can_reach_t 的点
int dista[MAXN];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;

    redge_cnt++;
    rto[redge_cnt] = u;
    rnxt[redge_cnt] = rhead[v];
    rhead[v] = redge_cnt;

    out_deg[u]++;
}

// 在反图上从 t 开始 BFS，标记哪些点在原图中能够到达 t。
void mark_can_reach_t() {
    queue<int> q;
    q.push(t);
    can_reach_t[t] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = rhead[u]; i != 0; i = rnxt[i]) {
            int v = rto[i];
            if (can_reach_t[v]) continue;
            can_reach_t[v] = true;
            q.push(v);
        }
    }
}

// 题目要求路径上的每个点，其所有出边指向的点都要直接或间接与 t 连通。
// 所以只要某个点存在一条出边通向“坏点”，它自己就不能出现在合法路径上。
void mark_safe_node() {
    for (int u = 1; u <= n; u++) {
        safe_node[u] = true;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (!can_reach_t[v]) {
                safe_node[u] = false;
                break;
            }
        }
    }
}

int bfs_shortest_path() {
    memset(dista, -1, sizeof(dista));

    if (!safe_node[s] || !safe_node[t]) return -1;

    queue<int> q;
    q.push(s);
    dista[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) return dista[u];

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (!safe_node[v]) continue;
            if (dista[v] != -1) continue;
            dista[v] = dista[u] + 1;
            q.push(v);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    cin >> s >> t;

    mark_can_reach_t();
    mark_safe_node();

    cout << bfs_shortest_path() << '\n';
    return 0;
}
