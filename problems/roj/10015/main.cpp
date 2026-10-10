/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 08:06
 * update_at: 2026-10-10 08:06
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXN = 500005;

int n, m, k, left_limit, right_limit;
vector<int> adj[MAXN]; // 树的邻接表

int is_red[MAXN];      // 初始具有超能力的红点
int is_green[MAXN];    // 到最近红点距离在区间内的绿点
int nearest_dist[MAXN];

int parent_node[MAXN];
int order_node[MAXN];
bool visited[MAXN];

ll red_count[MAXN];    // 当前根下子树/全树红点数量
ll green_count[MAXN];  // 当前根下子树/全树绿点数量
ll red_dist[MAXN];     // 到红点的距离和
ll red_dist2[MAXN];    // 到红点的距离平方和
ll green_dist[MAXN];   // 到绿点的距离和
ll answer[MAXN];

void clear_case() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        is_red[i] = 0;
        is_green[i] = 0;
        nearest_dist[i] = -1;
        parent_node[i] = 0;
        visited[i] = false;
        red_count[i] = 0;
        green_count[i] = 0;
        red_dist[i] = 0;
        red_dist2[i] = 0;
        green_dist[i] = 0;
        answer[i] = 0;
    }
}

void mark_green_points() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (is_red[i]) {
            nearest_dist[i] = 0;
            que.push(i);
        }
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (size_t j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            if (nearest_dist[v] == -1) {
                nearest_dist[v] = nearest_dist[u] + 1;
                que.push(v);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (nearest_dist[i] >= left_limit && nearest_dist[i] <= right_limit) {
            is_green[i] = 1;
        }
    }
}

int build_order() {
    int head = 0, tail = 0;
    order_node[tail++] = 1;
    visited[1] = true;

    while (head < tail) {
        int u = order_node[head++];
        for (size_t j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            if (!visited[v]) {
                visited[v] = true;
                parent_node[v] = u;
                order_node[tail++] = v;
            }
        }
    }
    return tail;
}

void calc_subtree(int order_size) {
    for (int pos = order_size - 1; pos >= 0; pos--) {
        int u = order_node[pos];
        red_count[u] = is_red[u];
        green_count[u] = is_green[u];
        for (size_t j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            if (v == parent_node[u]) {
                continue;
            }
            red_count[u] += red_count[v];
            green_count[u] += green_count[v];
            red_dist[u] += red_dist[v] + red_count[v];
            red_dist2[u] += red_dist2[v] + 2 * red_dist[v] + red_count[v];
            green_dist[u] += green_dist[v] + green_count[v];
        }
    }
}

void reroot_all(int order_size) {
    ll total_red = red_count[1];
    ll total_green = green_count[1];

    for (int pos = 0; pos < order_size; pos++) {
        int u = order_node[pos];
        for (size_t j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            if (v == parent_node[u]) {
                continue;
            }

            ll outside_red = total_red - red_count[v];
            ll outside_red_dist = red_dist[u] - red_dist[v] - red_count[v];
            ll outside_red_dist2 = red_dist2[u] - red_dist2[v] - 2 * red_dist[v] - red_count[v];
            red_dist[v] += outside_red_dist + outside_red;
            red_dist2[v] += outside_red_dist2 + 2 * outside_red_dist + outside_red;

            ll outside_green = total_green - green_count[v];
            ll outside_green_dist = green_dist[u] - green_dist[v] - green_count[v];
            green_dist[v] += outside_green_dist + outside_green;
        }
    }
}

void solve() {
    if (!(cin >> n >> m >> k >> left_limit >> right_limit)) {
        return;
    }
    clear_case();

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= m; i++) {
        int u;
        cin >> u;
        is_red[u] = 1; // 重复给出的红点只算一个
    }

    mark_green_points();
    int order_size = build_order();
    calc_subtree(order_size);
    reroot_all(order_size);

    for (int i = 1; i <= n; i++) {
        answer[i] = red_dist2[i] + green_dist[i];
    }

    for (int i = 1; i <= k; i++) {
        int query_node;
        cin >> query_node;
        cout << answer[query_node] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
