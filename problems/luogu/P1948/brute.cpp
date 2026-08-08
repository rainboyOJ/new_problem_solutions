#include <bits/stdc++.h>
using namespace std;

// brute.cpp：按“已经免费使用几条边”做 Dijkstra，适合小数据对拍。

const int MAXN = 105;
const int MAXP = 1005;
const int INF = 1000000000;

struct State {
    int cost, node, free_used;
};

struct CmpState {
    bool operator()(const State &a, const State &b) const {
        return a.cost > b.cost;
    }
};

int n, p, k;
int head[MAXN], to[MAXP * 2], weight_edge[MAXP * 2], nxt[MAXP * 2], edge_cnt;
int dist_value[MAXN][MAXN]; // dist_value[u][c]：到 u，已免费 c 条边时的最小最大付费边。

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> p >> k;
    for (int i = 1; i <= p; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        add_edge(a, b, l);
        add_edge(b, a, l);
    }
}

int dijkstra() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dist_value[i][j] = INF;
        }
    }

    priority_queue<State, vector<State>, CmpState> pq;
    dist_value[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (cur.cost != dist_value[cur.node][cur.free_used]) {
            continue;
        }

        for (int i = head[cur.node]; i != 0; i = nxt[i]) {
            int v = to[i];
            int w = weight_edge[i];

            int pay_cost = max(cur.cost, w);
            if (pay_cost < dist_value[v][cur.free_used]) {
                dist_value[v][cur.free_used] = pay_cost;
                pq.push({pay_cost, v, cur.free_used});
            }

            if (cur.free_used < k && cur.cost < dist_value[v][cur.free_used + 1]) {
                dist_value[v][cur.free_used + 1] = cur.cost;
                pq.push({cur.cost, v, cur.free_used + 1});
            }
        }
    }

    int answer = INF;
    for (int i = 0; i <= k; i++) {
        answer = min(answer, dist_value[n][i]);
    }
    if (answer == INF) {
        return -1;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << dijkstra() << '\n';

    return 0;
}
