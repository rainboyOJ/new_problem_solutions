#include <bits/stdc++.h>
using namespace std;

const int MAXF = 500 + 5;
const int MAXP = 1000 * 2 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int f, p, c, m_limit;
int head[MAXF], to[MAXP], nxt[MAXP], w[MAXP], edge_cnt;
int cow_pos[105];
long long dist_arr[MAXF];
bool vis[MAXF];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= f; i++) {
        head[i] = 0;
    }
}

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra(int start) {
    for (int i = 1; i <= f; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
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
            int v = to[i];
            long long nd = dist_arr[u] + w[i];
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                pq.push({v, nd});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> f >> p >> c >> m_limit;
    init_graph();

    for (int i = 1; i <= p; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);
    }

    for (int i = 1; i <= c; i++) {
        cin >> cow_pos[i];
    }

    // 1 号草地是被盗谷仓，只需要从这里做一次单源最短路。
    dijkstra(1);

    vector<int> answer;
    for (int i = 1; i <= c; i++) {
        if (dist_arr[cow_pos[i]] <= m_limit) {
            answer.push_back(i);
        }
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
