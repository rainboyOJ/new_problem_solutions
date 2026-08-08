#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 INF = (1LL << 62);
const int FREE_BALL = 0;
const int CONTROL = 1;

struct HeapNode {
    i64 dist;
    int state;
    int x, y;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int H, W, n;
i64 A, B, C;
vector<int> sx, sy;
vector<i64> player_cost;
vector<i64> dist_arr;

int cell_id(int x, int y) {
    return x * (W + 1) + y;
}

int node_id(int state, int x, int y) {
    return state * (H + 1) * (W + 1) + cell_id(x, y);
}

void try_relax(priority_queue<HeapNode> &pq, int state, int x, int y, i64 nd) {
    int id = node_id(state, x, y);
    if (nd < dist_arr[id]) {
        dist_arr[id] = nd;
        pq.push({nd, state, x, y});
    }
}

void prepare_player_cost() {
    int total = (H + 1) * (W + 1);
    vector<int> step_dist(total, -1);
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        int id = cell_id(sx[i], sy[i]);
        if (step_dist[id] == -1) {
            step_dist[id] = 0;
            q.push(id);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int x = cur / (W + 1);
        int y = cur % (W + 1);

        if (x > 0) {
            int nid = cell_id(x - 1, y);
            if (step_dist[nid] == -1) {
                step_dist[nid] = step_dist[cur] + 1;
                q.push(nid);
            }
        }
        if (x < H) {
            int nid = cell_id(x + 1, y);
            if (step_dist[nid] == -1) {
                step_dist[nid] = step_dist[cur] + 1;
                q.push(nid);
            }
        }
        if (y > 0) {
            int nid = cell_id(x, y - 1);
            if (step_dist[nid] == -1) {
                step_dist[nid] = step_dist[cur] + 1;
                q.push(nid);
            }
        }
        if (y < W) {
            int nid = cell_id(x, y + 1);
            if (step_dist[nid] == -1) {
                step_dist[nid] = step_dist[cur] + 1;
                q.push(nid);
            }
        }
    }

    player_cost.assign(total, 0);
    for (int x = 0; x <= H; x++) {
        for (int y = 0; y <= W; y++) {
            int id = cell_id(x, y);
            player_cost[id] = (i64) step_dist[id] * C;
        }
    }
}

void dijkstra() {
    int total_nodes = 2 * (H + 1) * (W + 1);
    dist_arr.assign(total_nodes, INF);

    priority_queue<HeapNode> pq;
    try_relax(pq, CONTROL, sx[1], sy[1], 0);

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int id = node_id(cur.state, cur.x, cur.y);
        if (cur.dist != dist_arr[id]) {
            continue;
        }

        int x = cur.x;
        int y = cur.y;
        i64 now = cur.dist;

        if (cur.state == FREE_BALL) {
            try_relax(pq, CONTROL, x, y, now + player_cost[cell_id(x, y)]);
            continue;
        }

        if (x > 0) try_relax(pq, CONTROL, x - 1, y, now + C);
        if (x < H) try_relax(pq, CONTROL, x + 1, y, now + C);
        if (y > 0) try_relax(pq, CONTROL, x, y - 1, now + C);
        if (y < W) try_relax(pq, CONTROL, x, y + 1, now + C);

        for (int nx = 0; nx <= H; nx++) {
            if (nx == x) {
                continue;
            }
            i64 cost = now + (i64) abs(nx - x) * A + B;
            try_relax(pq, FREE_BALL, nx, y, cost);
        }
        for (int ny = 0; ny <= W; ny++) {
            if (ny == y) {
                continue;
            }
            i64 cost = now + (i64) abs(ny - y) * A + B;
            try_relax(pq, FREE_BALL, x, ny, cost);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> W;
    cin >> A >> B >> C;
    cin >> n;

    sx.assign(n + 1, 0);
    sy.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> sx[i] >> sy[i];
    }

    prepare_player_cost();
    dijkstra();

    int tx = sx[n];
    int ty = sy[n];
    i64 answer = min(
        dist_arr[node_id(FREE_BALL, tx, ty)],
        dist_arr[node_id(CONTROL, tx, ty)]
    );

    cout << answer << '\n';
    return 0;
}
