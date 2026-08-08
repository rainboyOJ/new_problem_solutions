#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOG = 20;

struct Query {
    int u, v, lca_node;
    long long length;
};

int n, m;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_weight[MAXN * 2], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG + 1];          // up[x][j] 表示 x 的 2^j 级祖先。
int parent_edge_weight[MAXN];   // parent_edge_weight[x] 表示 x 到父亲这条边的权值。
long long dist_root[MAXN];      // 根到每个点的路径长度。
int diff_count[MAXN];           // check() 中的边差分计数。
vector<int> bfs_order;          // BFS 顺序，反向使用即可自底向上汇总。
Query query_data[MAXN];

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_tree() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
}

void build_lca() {
    queue<int> que;
    que.push(1);
    depth_node[1] = 1;
    bfs_order.reserve(n);

    // 用 BFS 建父亲、深度和根到点距离，避免深递归爆栈。
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        bfs_order.push_back(u);

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
            dist_root[v] = dist_root[u] + edge_weight[i];
            parent_edge_weight[v] = edge_weight[i];
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

void read_queries_and_precompute(long long &right_bound) {
    right_bound = 0;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int g = lca(u, v);
        long long len = dist_root[u] + dist_root[v] - 2LL * dist_root[g];
        query_data[i] = {u, v, g, len};
        right_bound = max(right_bound, len);
    }
}

bool check(long long limit) {
    for (int i = 1; i <= n; i++) {
        diff_count[i] = 0;
    }

    int bad_count = 0;
    long long need_reduce = 0;

    for (int i = 1; i <= m; i++) {
        if (query_data[i].length <= limit) {
            continue;
        }

        bad_count++;
        need_reduce = max(need_reduce, query_data[i].length - limit);

        // 只统计超出 limit 的路径。若要一次改边让它们都变短，
        // 这条边必须被所有超标路径共同经过。
        int u = query_data[i].u;
        int v = query_data[i].v;
        int g = query_data[i].lca_node;
        diff_count[u]++;
        diff_count[v]++;
        diff_count[g] -= 2;
    }

    if (bad_count == 0) {
        return true;
    }

    long long best_common_edge = 0;

    // 反向 BFS 序等价于从叶子向根汇总。
    // diff_count[x] 汇总后表示边 parent[x] - x 被多少条超标路径经过。
    for (int i = (int)bfs_order.size() - 1; i >= 0; i--) {
        int u = bfs_order[i];
        if (diff_count[u] == bad_count) {
            best_common_edge = max(best_common_edge, (long long)parent_edge_weight[u]);
        }
        if (up[u][0] != 0) {
            diff_count[up[u][0]] += diff_count[u];
        }
    }

    // 最长的超标路径至少需要被缩短 need_reduce。
    return best_common_edge >= need_reduce;
}

void solve() {
    build_lca();

    long long right_bound = 0;
    read_queries_and_precompute(right_bound);

    long long left = 0;
    long long right = right_bound;
    long long answer = right_bound;

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_tree();
    solve();

    return 0;
}
