#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1055;

int n;
int target_x, target_y;
int x[MAXN], y[MAXN], r[MAXN];
vector<int> g[MAXN];
int root_id, target_id;
int parent_node[MAXN];
long double speed[MAXN];

bool touch(int i, int j) {
    long long dx = 1LL * x[i] - x[j];
    long long dy = 1LL * y[i] - y[j];
    long long sum_r = 1LL * r[i] + r[j];
    return dx * dx + dy * dy == sum_r * sum_r;
}

void build_graph() {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (touch(i, j)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
}

void find_special_nodes() {
    root_id = 0;
    target_id = 0;
    for (int i = 1; i <= n; i++) {
        if (x[i] == 0 && y[i] == 0) {
            root_id = i;
        }
        if (x[i] == target_x && y[i] == target_y) {
            target_id = i;
        }
    }
}

void bfs() {
    memset(parent_node, -1, sizeof(parent_node));

    queue<int> q;
    parent_node[root_id] = 0;
    speed[root_id] = 10000.0L;
    q.push(root_id);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == target_id) {
            return;
        }

        for (int i = 0; i < (int) g[u].size(); i++) {
            int v = g[u][i];
            if (parent_node[v] != -1) {
                continue;
            }
            parent_node[v] = u;
            // 两个相切滚轮的线速度相同，所以角速度与半径成反比，方向相反。
            speed[v] = -speed[u] * (long double) r[u] / r[v];
            q.push(v);
        }
    }
}

long long calc_answer() {
    long double sum = 0.0L;
    int cur = target_id;
    while (cur != 0) {
        sum += fabsl(speed[cur]);
        if (cur == root_id) {
            break;
        }
        cur = parent_node[cur];
    }
    return (long long) floorl(sum + 1e-12L);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target_x >> target_y;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    build_graph();
    find_special_nodes();
    bfs();

    cout << calc_answer() << '\n';
    return 0;
}
