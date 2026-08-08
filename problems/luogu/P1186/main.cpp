#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 5;
const int MAXM = 20000 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m;
int eu[MAXM], ev[MAXM];
long long ew[MAXM];

int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], edge_id[MAXM * 2], edge_cnt;
long long dist_arr[MAXN];
bool vis[MAXN];
int parent_node[MAXN], parent_edge[MAXN];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
}

void add_edge(int u, int v, int id) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_id[edge_cnt] = id;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra(int start, bool save_parent, int banned_id) {
    for (int i = 1; i <= n; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
        if (save_parent) {
            parent_node[i] = 0;
            parent_edge[i] = 0;
        }
    }

    priority_queue<HeapNode> pq;
    dist_arr[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int id = edge_id[i];
            if (id == banned_id) {
                continue;
            }

            int v = to[i];
            long long nd = dist_arr[u] + ew[id];
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                if (save_parent) {
                    parent_node[v] = u;
                    parent_edge[v] = id;
                }
                pq.push({v, nd});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph();

    for (int i = 1; i <= m; i++) {
        cin >> eu[i] >> ev[i] >> ew[i];
        add_edge(eu[i], ev[i], i);
        add_edge(ev[i], eu[i], i);
    }

    dijkstra(1, true, 0);

    vector<int> path_edges;
    int cur = n;
    while (cur != 1) {
        path_edges.push_back(parent_edge[cur]);
        cur = parent_node[cur];
    }

    long long answer = 0;

    // 只有这条已知最短路上的边被封掉，才可能让最短路变长。
    for (size_t i = 0; i < path_edges.size(); i++) {
        int banned_id = path_edges[i];
        dijkstra(1, false, banned_id);
        answer = max(answer, dist_arr[n]);
    }

    cout << answer << '\n';

    return 0;
}
