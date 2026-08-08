#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int LOG = 16;

int n, k;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG + 1];      // up[x][j] 表示 x 的 2^j 级祖先。
long long diff_count[MAXN]; // 树上点差分数组，最后自底向上汇总成每个点的流量。
long long answer;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
}

void build_lca() {
    queue<int> que;
    que.push(1);
    depth_node[1] = 1;

    // BFS 建树，避免深递归在链形树上爆栈。
    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int j = 1; j <= LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;
            }
            up[v][0] = u;
            depth_node[v] = depth_node[u] + 1;
            que.push(v);
        }
    }
}

int lca(int x, int y) {
    if (depth_node[x] < depth_node[y]) {
        swap(x, y);
    }

    int diff = depth_node[x] - depth_node[y];
    for (int j = LOG; j >= 0; j--) {
        if ((diff & (1 << j)) != 0) {
            x = up[x][j];
        }
    }

    if (x == y) {
        return x;
    }

    for (int j = LOG; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            x = up[x][j];
            y = up[y][j];
        }
    }

    return up[x][0];
}

void collect_answer() {
    vector<int> order;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        order.push_back(u);
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;
            }
            que.push(v);
        }
    }

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        answer = max(answer, diff_count[u]);
        if (up[u][0] != 0) {
            diff_count[up[u][0]] += diff_count[u];
        }
    }
}

void solve() {
    build_lca();

    for (int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        int g = lca(u, v);

        // 点差分：让路径 u -> v 上所有点最终都加 1。
        // u、v 两端各加一；lca 和 lca 的父亲负责截断向根方向的多余贡献。
        diff_count[u]++;
        diff_count[v]++;
        diff_count[g]--;
        if (up[g][0] != 0) {
            diff_count[up[g][0]]--;
        }
    }

    collect_answer();
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
