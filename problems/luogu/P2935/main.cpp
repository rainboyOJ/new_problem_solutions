#include <bits/stdc++.h>
using namespace std;

const int MAXP = 500 + 5;
const int MAXC = 8000 * 2 + 5;
const long long INF = (1LL << 60);

struct Node {
    int u;
    long long dist;

    bool operator < (const Node &other) const {
        return dist > other.dist;
    }
};

int p, f, c;
int fav[MAXP];

int head[MAXP], to[MAXC], nxt[MAXC], weight_arr[MAXC], edge_cnt;
long long dist_arr[MAXP];
long long total_dist[MAXP];
bool vis[MAXP];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= p; i++) {
        head[i] = 0;
        total_dist[i] = 0;
    }
}

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_arr[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 从一个“喜欢的牧场”出发跑单源最短路，
// 再把它到所有点的距离累加到 total_dist 里。
void dijkstra(int start) {
    for (int i = 1; i <= p; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    priority_queue<Node> pq;
    dist_arr[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long nd = dist_arr[u] + weight_arr[i];
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                pq.push({v, nd});
            }
        }
    }

    for (int i = 1; i <= p; i++) {
        total_dist[i] += dist_arr[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p >> f >> c;
    init_graph();

    for (int i = 1; i <= f; i++) {
        cin >> fav[i];
    }

    for (int i = 1; i <= c; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    // 图是无向图，所以 dist(候选点, 喜欢点) = dist(喜欢点, 候选点)。
    // 与其枚举每个候选点都跑一次最短路，不如从每个喜欢点跑一次，
    // 再把距离累加到所有候选点上。
    for (int i = 1; i <= f; i++) {
        dijkstra(fav[i]);
    }

    int answer = 1;
    for (int i = 2; i <= p; i++) {
        if (total_dist[i] < total_dist[answer]) {
            answer = i;
        }
    }

    cout << answer << '\n';

    return 0;
}
