#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
int parent_node[MAXN];
int subtree_size[MAXN];
int depth_node[MAXN];
long long dist_sum[MAXN]; // dist_sum[u] 表示以 u 为根时，所有点深度之和。
vector<int> order_nodes;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
}

void build_order() {
    order_nodes.reserve(n);
    queue<int> que;
    que.push(1);
    parent_node[1] = 0;
    depth_node[1] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        order_nodes.push_back(u);

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            depth_node[v] = depth_node[u] + 1;
            que.push(v);
        }
    }
}

void solve() {
    build_order();

    long long root_sum = 0;
    for (int i = 0; i < (int)order_nodes.size(); i++) {
        int u = order_nodes[i];
        subtree_size[u] = 1;
        root_sum += depth_node[u];
    }
    dist_sum[1] = root_sum;

    for (int i = (int)order_nodes.size() - 1; i >= 0; i--) {
        int u = order_nodes[i];
        if (parent_node[u] != 0) {
            subtree_size[parent_node[u]] += subtree_size[u];
        }
    }

    for (int i = 0; i < (int)order_nodes.size(); i++) {
        int u = order_nodes[i];
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (v == parent_node[u]) {
                continue;
            }

            // 根从 u 换到孩子 v：
            // v 子树内的点深度都 -1，其余点深度都 +1。
            dist_sum[v] = dist_sum[u] - subtree_size[v] + (n - subtree_size[v]);
        }
    }

    int best_node = 1;
    for (int i = 2; i <= n; i++) {
        if (dist_sum[i] > dist_sum[best_node]) {
            best_node = i;
        }
    }

    cout << best_node << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
