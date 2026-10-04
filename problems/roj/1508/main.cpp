/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:26
 * update_at: 2026-10-05 05:26
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;    // 点数上限
const int MAXM = 100005;  // 边数上限
const long long INF = 4000000000000000000LL; // 无穷大哨兵，远大于任何合法最短路

typedef long long ll;

ll n;          // 点数
ll m;          // 边数
ll start_node; // 源点 S

int head[MAXN];  // 链式前向星：head[u] 是以 u 为起点的第一条边编号
int to[MAXM];    // to[i] 是第 i 条边的终点
int nxt_edge[MAXM]; // nxt_edge[i] 是 u 的下一条边编号
ll weight[MAXM]; // weight[i] 是第 i 条边的边权，可能为负
int edge_idx;    // 已加入的边数

ll dist[MAXN];      // dist[v] 是当前求出的到 v 的最短距离
int relax_cnt[MAXN]; // relax_cnt[v] 是当前最短路包含的边数，用于判负环
bool in_queue[MAXN]; // 标记点是否在 SPFA 队列中

// 加入一条 u -> v、权值为 w 的有向边。
void add_edge(int u, int v, ll w) {
    edge_idx++;
    to[edge_idx] = v;
    weight[edge_idx] = w;
    nxt_edge[edge_idx] = head[u];
    head[u] = edge_idx;
}

// 全图判负环：所有点一起入队（等价于建一个到各点权为 0 的超级源点）。
// 若某点的最短路已被松弛出 >= n 条边，说明路径上必有重复点，即存在负权回路。
bool has_negative_cycle() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        dist[i] = 0; // 全员初始为 0，负环在任意连通块中都能被发现
        relax_cnt[i] = 0;
        in_queue[i] = true;
        q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int i = head[u]; i != 0; i = nxt_edge[i]) {
            int v = to[i];
            if (dist[u] + weight[i] < dist[v]) {
                dist[v] = dist[u] + weight[i];
                relax_cnt[v] = relax_cnt[u] + 1;
                if (relax_cnt[v] >= n) {
                    return true;
                }
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

// 以 src 为源点做 SPFA，求单源最短路；调用前保证全图无负权回路。
void shortest_path(ll src) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        in_queue[i] = false;
    }
    dist[src] = 0;
    in_queue[src] = true;
    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int i = head[u]; i != 0; i = nxt_edge[i]) {
            int v = to[i];
            if (dist[u] + weight[i] < dist[v]) {
                dist[v] = dist[u] + weight[i];
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

void read_input() {
    cin >> n >> m >> start_node;
    for (ll i = 1; i <= m; i++) {
        int u;
        int v;
        ll w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    if (has_negative_cycle()) {
        cout << -1 << "\n";
        return 0;
    }

    shortest_path(start_node);
    for (int i = 1; i <= n; i++) {
        if (i == start_node) {
            cout << 0 << "\n";
        } else if (dist[i] == INF) {
            cout << "NoPath" << "\n";
        } else {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}
