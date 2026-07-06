#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
vector<int> g[MAXN];
int parent_node[MAXN];
int order_arr[MAXN], order_cnt;
int subtree_size[MAXN];      // subtree_size[u] 表示以 1 为根时 u 子树的大小
long long dist_sum[MAXN];    // dist_sum[u] 表示所有点到 u 的距离和

void compute_depth_sum_and_size() {
    queue<int> q;
    static int depth[MAXN];
    q.push(1);
    parent_node[1] = 0;
    depth[1] = 0;
    order_cnt = 0;
    dist_sum[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order_arr[++order_cnt] = u;
        dist_sum[1] += depth[u];

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_node[u]) continue;
            parent_node[v] = u;
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        subtree_size[i] = 1;
    }
    for (int i = order_cnt; i >= 1; i--) {
        int u = order_arr[i];
        if (parent_node[u] != 0) {
            subtree_size[parent_node[u]] += subtree_size[u];
        }
    }
}

void reroot_dp() {
    for (int i = 1; i <= order_cnt; i++) {
        int u = order_arr[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (parent_node[v] != u) continue;

            // 根从 u 移到儿子 v：
            // v 子树里的点距离都 -1，其余点距离都 +1。
            dist_sum[v] = dist_sum[u] + (long long)n - 2LL * subtree_size[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    compute_depth_sum_and_size();
    reroot_dp();

    int best_node = 1;
    long long best_sum = dist_sum[1];
    for (int i = 2; i <= n; i++) {
        if (dist_sum[i] < best_sum) {
            best_sum = dist_sum[i];
            best_node = i;
        }
    }

    cout << best_node << " " << best_sum << "\n";

    return 0;
}
