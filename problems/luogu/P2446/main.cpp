#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000 + 5;
const int MAXM = 70000 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], edge_cnt;

long long answer[MAXN];      // 城市最早被摧毁的时间
long long road_arrive[MAXN]; // 已经摧毁的城市中，最早什么时候能派机器人到这个城市门口
long long shield_need[MAXN]; // 所有前置结界发生器被摧毁后的最晚时间
int remain_need[MAXN];       // 还有多少前置发生器没被摧毁
bool vis[MAXN];

vector<int> depend[MAXN];    // 城市 u 的发生器会影响哪些城市

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        depend[i].clear();
    }
}

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void try_update_city(int v, priority_queue<HeapNode> &pq) {
    if (vis[v]) {
        return;
    }
    if (remain_need[v] != 0) {
        return;
    }
    if (road_arrive[v] >= INF / 2) {
        return;
    }

    long long cand = max(road_arrive[v], shield_need[v]);
    if (cand < answer[v]) {
        answer[v] = cand;
        pq.push({v, cand});
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        answer[i] = INF;
        road_arrive[i] = INF;
        shield_need[i] = 0;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;

    // 城市 1 已经被我方控制，时间记为 0。
    answer[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        // 从已经摧毁的城市 u 出发，派机器人沿单向道路去其他城市门口。
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long nd = answer[u] + w[i];
            if (nd < road_arrive[v]) {
                road_arrive[v] = nd;
                try_update_city(v, pq);
            }
        }

        // u 城市里的发生器已经被摧毁，它会解开一批城市的结界限制。
        for (size_t i = 0; i < depend[u].size(); i++) {
            int v = depend[u][i];
            remain_need[v]--;
            if (answer[u] > shield_need[v]) {
                shield_need[v] = answer[u];
            }
            try_update_city(v, pq);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
    }

    for (int city = 1; city <= n; city++) {
        int k;
        cin >> k;
        remain_need[city] = k;
        for (int j = 1; j <= k; j++) {
            int generator_city;
            cin >> generator_city;
            depend[generator_city].push_back(city);
        }
    }

    solve();
    cout << answer[n] << '\n';

    return 0;
}
