#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOG = 20;

int n;
int route_node[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG + 1];
long long diff_count[MAXN];
long long answer[MAXN];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> route_node[i];
    }
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
    order.reserve(n);
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
        answer[u] += diff_count[u];
        if (up[u][0] != 0) {
            diff_count[up[u][0]] += diff_count[u];
        }
    }
}

void solve() {
    build_lca();

    for (int i = 1; i < n; i++) {
        int u = route_node[i];
        int v = route_node[i + 1];
        int g = lca(u, v);
        diff_count[u]++;
        diff_count[v]++;
        diff_count[g]--;
        if (up[g][0] != 0) {
            diff_count[up[g][0]]--;
        }
    }

    collect_answer();

    // 每个中间到达点既是上一段终点又是下一段起点，只应拿一次糖。
    for (int i = 2; i <= n; i++) {
        answer[route_node[i]]--;
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
