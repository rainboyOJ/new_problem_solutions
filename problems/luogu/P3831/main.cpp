#include <bits/stdc++.h>
using namespace std;

const int MAXP = 100000 + 5;
const int MAXV = MAXP * 2 + 10;
const int MAXE = 1200000 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m;
int px[MAXP], py[MAXP];
bool can_transfer[MAXP];
int point_cnt;
int sx, sy, tx, ty;

int head[MAXV], to[MAXE], nxt[MAXE], w[MAXE], edge_cnt;
long long dist_arr[MAXV];
bool vis[MAXV];

int row_order[MAXP], col_order[MAXP];

int row_id(int id) {
    return id * 2 - 1;
}

int col_id(int id) {
    return id * 2;
}

bool cmp_row(int a, int b) {
    if (px[a] != px[b]) {
        return px[a] < px[b];
    }
    if (py[a] != py[b]) {
        return py[a] < py[b];
    }
    return a < b;
}

bool cmp_col(int a, int b) {
    if (py[a] != py[b]) {
        return py[a] < py[b];
    }
    if (px[a] != px[b]) {
        return px[a] < px[b];
    }
    return a < b;
}

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= row_id(point_cnt) + 1; i++) {
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

void build_graph() {
    init_graph();

    // 换乘站可以在站内从横线切到竖线，代价 1。
    for (int i = 1; i <= m; i++) {
        add_edge(row_id(i), col_id(i), 1);
        add_edge(col_id(i), row_id(i), 1);
    }

    for (int i = 1; i <= point_cnt; i++) {
        row_order[i] = i;
        col_order[i] = i;
    }

    sort(row_order + 1, row_order + point_cnt + 1, cmp_row);
    sort(col_order + 1, col_order + point_cnt + 1, cmp_col);

    // 同一横线上的关键点，只需要连相邻的两个。
    for (int i = 2; i <= point_cnt; i++) {
        int a = row_order[i - 1];
        int b = row_order[i];
        if (px[a] != px[b]) {
            continue;
        }
        int len = (py[b] - py[a]) * 2;
        add_edge(row_id(a), row_id(b), len);
        add_edge(row_id(b), row_id(a), len);
    }

    // 同一竖线上的关键点，也只需要连相邻两个。
    for (int i = 2; i <= point_cnt; i++) {
        int a = col_order[i - 1];
        int b = col_order[i];
        if (py[a] != py[b]) {
            continue;
        }
        int len = (px[b] - px[a]) * 2;
        add_edge(col_id(a), col_id(b), len);
        add_edge(col_id(b), col_id(a), len);
    }
}

void dijkstra(int start_point) {
    int tot = point_cnt * 2;
    for (int i = 1; i <= tot; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;

    // 出发点可以直接选择坐横线或者竖线，不需要换乘时间。
    dist_arr[row_id(start_point)] = 0;
    dist_arr[col_id(start_point)] = 0;
    pq.push({row_id(start_point), 0});
    pq.push({col_id(start_point), 0});

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

    cin >> n >> m;

    point_cnt = m;
    for (int i = 1; i <= m; i++) {
        cin >> px[i] >> py[i];
        can_transfer[i] = true;
    }

    cin >> sx >> sy >> tx >> ty;

    point_cnt++;
    px[point_cnt] = sx;
    py[point_cnt] = sy;
    int start_point = point_cnt;

    point_cnt++;
    px[point_cnt] = tx;
    py[point_cnt] = ty;
    int end_point = point_cnt;

    build_graph();
    dijkstra(start_point);

    long long answer = min(dist_arr[row_id(end_point)], dist_arr[col_id(end_point)]);

    if (answer >= INF / 2) {
        cout << -1 << '\n';
    }
    else {
        cout << answer << '\n';
    }

    return 0;
}
