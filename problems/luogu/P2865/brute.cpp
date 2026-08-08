#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 2005;

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, r;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], edge_cnt;
vector<long long> seen_dist[MAXN];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        seen_dist[i].clear();
    }
}

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r;
    init_graph();

    for (int i = 1; i <= r; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);
    }

    priority_queue<HeapNode> pq;
    pq.push({1, 0});

    // 更直接的想法：
    // 按路径长度从小到大枚举所有“走到某个点的候选路径”。
    // 某个点第一次出现的新距离是最短路，第二个不同的距离就是严格次短路。
    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        long long d = cur.dist;

        if (!seen_dist[u].empty() && seen_dist[u].back() == d) {
            continue;
        }
        if (seen_dist[u].size() >= 2) {
            continue;
        }

        seen_dist[u].push_back(d);
        if (u == n && seen_dist[u].size() == 2) {
            cout << d << '\n';
            return 0;
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            pq.push({v, d + w[i]});
        }
    }

    return 0;
}
