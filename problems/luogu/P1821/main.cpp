#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 5;
const int MAXM = 100000 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m, x;

// 原图：求 x -> i 的最短路
int head1[MAXN], to1[MAXM], nxt1[MAXM], w1[MAXM], cnt1;
// 反图：求 i -> x 的最短路，等价于在反图里求 x -> i
int head2[MAXN], to2[MAXM], nxt2[MAXM], w2[MAXM], cnt2;

long long dist_go[MAXN];
long long dist_back[MAXN];
bool vis[MAXN];

void init_graph() {
    cnt1 = 0;
    cnt2 = 0;
    for (int i = 1; i <= n; i++) {
        head1[i] = 0;
        head2[i] = 0;
    }
}

void add_edge(int head[], int to[], int nxt[], int w[], int &cnt, int u, int v, int len) {
    cnt++;
    to[cnt] = v;
    w[cnt] = len;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

// 在给定的图上，从 start 跑一次 Dijkstra。
void dijkstra(int start, int head[], int to[], int nxt[], int w[], long long dist[]) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;
    dist[start] = 0;
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
            long long nd = dist[u] + w[i];
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({v, nd});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> x;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;

        add_edge(head1, to1, nxt1, w1, cnt1, u, v, len);
        add_edge(head2, to2, nxt2, w2, cnt2, v, u, len);
    }

    dijkstra(x, head1, to1, nxt1, w1, dist_go);
    dijkstra(x, head2, to2, nxt2, w2, dist_back);

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, dist_go[i] + dist_back[i]);
    }

    cout << answer << '\n';

    return 0;
}
