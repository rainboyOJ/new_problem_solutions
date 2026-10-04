/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:18
 * update_at: 2026-10-05 05:18
 */
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 105;
const int MAXM = 305;
const int MAX_COST = 10000; // 简单路径边数不超过 n-1，总费用最多 99*100，取 10000 作上界
const int INF = 1000000000;

typedef long long ll;

ll n, m, s, e;

// 链式前向星存无向图，每条无向边拆成两条有向边
int head[MAXN];
int nxt[2 * MAXM];
int to[2 * MAXM];
int edge_cost[2 * MAXM]; // 边的费用
int edge_time[2 * MAXM]; // 边的时间
int edge_cnt;

// dist[u][c]：到达节点 u 且累计费用恰好为 c 时的最小时间
int dist[MAXN][MAX_COST + 1];

struct State {
    int t; // 已累计的时间
    int c; // 已累计的费用
    int u; // 当前节点
    bool operator<(const State &other) const {
        return t > other.t; // 时间小的优先，配合 priority_queue 实现小根堆
    }
};

// 加入一条 u -> v 的有向边，携带费用 c 和时间 t。
void add_edge(int u, int v, int c, int t) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_cost[edge_cnt] = c;
    edge_time[edge_cnt] = t;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 以费用为状态维度拆点，在 (节点, 费用) 状态图上跑 Dijkstra。
void dijkstra() {
    for (int u = 1; u <= n; u++) {
        for (int c = 0; c <= MAX_COST; c++) {
            dist[u][c] = INF;
        }
    }
    dist[s][0] = 0;

    priority_queue<State> pq;
    State start;
    start.t = 0;
    start.c = 0;
    start.u = s;
    pq.push(start);

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        if (cur.t > dist[cur.u][cur.c]) {
            continue; // 过期状态，跳过
        }
        for (int i = head[cur.u]; i != 0; i = nxt[i]) {
            int v = to[i];
            int nc = cur.c + edge_cost[i];
            int nt = cur.t + edge_time[i];
            if (nc > MAX_COST) {
                continue;
            }
            if (nt < dist[v][nc]) {
                dist[v][nc] = nt;
                State nxt_state;
                nxt_state.t = nt;
                nxt_state.c = nc;
                nxt_state.u = v;
                pq.push(nxt_state);
            }
        }
    }
}

// 按费用升序扫描终点状态，只有时间严格小于历史最小值时才是 Pareto 最优解。
int count_pareto() {
    int min_time = INF;
    int ans = 0;
    for (int c = 0; c <= MAX_COST; c++) {
        int t = dist[e][c];
        if (t < min_time) {
            min_time = t;
            ans++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s >> e;
    for (ll i = 0; i < m; i++) {
        int p, r, c, t; // 端点编号不超过 100，费用与时间不超过 100，用 int 即可
        cin >> p >> r >> c >> t;
        add_edge(p, r, c, t);
        add_edge(r, p, c, t);
    }

    dijkstra();
    cout << count_pareto() << "\n";

    return 0;
}
