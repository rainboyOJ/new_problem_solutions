#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 50005;
const int LOG = 15;
const int INF = 1000000000;

struct Edge {
    int u, v, w;
};

int n, m, q;
Edge edge[MAXM];

int father[MAXN];
int head[MAXN], to[MAXN * 2], weight_edge[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG];
int min_edge[MAXN][LOG]; // min_edge[x][j] 表示 x 向上跳 2^j 条边时经过的最小限重。
int component[MAXN];

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

int find_root(int x) {
    if (father[x] == x) {
        return x;
    }
    father[x] = find_root(father[x]);
    return father[x];
}

bool merge_set(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx == ry) {
        return false;
    }
    father[rx] = ry;
    return true;
}

void add_tree_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }
}

void build_maximum_spanning_forest() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }
    sort(edge + 1, edge + m + 1, cmp_edge);

    for (int i = 1; i <= m; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;
        if (merge_set(u, v)) {
            add_tree_edge(u, v, w);
            add_tree_edge(v, u, w);
        }
    }
}

void bfs_component(int start, int cid) {
    queue<int> que;
    que.push(start);
    component[start] = cid;
    depth_node[start] = 1;
    up[start][0] = 0;
    min_edge[start][0] = INF;

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
            min_edge[u][j] = min(min_edge[u][j - 1], min_edge[up[u][j - 1]][j - 1]);
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;
            }
            component[v] = cid;
            depth_node[v] = depth_node[u] + 1;
            up[v][0] = u;
            min_edge[v][0] = weight_edge[i];
            que.push(v);
        }
    }
}

void prepare_lca() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < LOG; j++) {
            min_edge[i][j] = INF;
        }
    }

    int cid = 0;
    for (int i = 1; i <= n; i++) {
        if (component[i] == 0) {
            cid++;
            bfs_component(i, cid);
        }
    }
}

int query(int x, int y) {
    if (component[x] != component[y]) {
        return -1;
    }

    int answer = INF;
    if (depth_node[x] < depth_node[y]) {
        swap(x, y);
    }

    int diff = depth_node[x] - depth_node[y];
    for (int j = LOG - 1; j >= 0; j--) {
        if ((diff & (1 << j)) != 0) {
            answer = min(answer, min_edge[x][j]);
            x = up[x][j];
        }
    }

    if (x == y) {
        return answer;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            answer = min(answer, min_edge[x][j]);
            answer = min(answer, min_edge[y][j]);
            x = up[x][j];
            y = up[y][j];
        }
    }

    answer = min(answer, min_edge[x][0]);
    answer = min(answer, min_edge[y][0]);
    return answer;
}

void solve() {
    build_maximum_spanning_forest();
    prepare_lca();

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
