#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300000 + 5;
const int LOG = 20;

struct Frame {
    int u;
    int before1;
    int before2;
};

int n, m;
vector<int> g[MAXN];
int w[MAXN];

int parent_arr[MAXN];
int depth_arr[MAXN];
int up[MAXN][LOG];
int iter_idx[MAXN];

// 第一类事件：处理 s -> lca 这一段，key = depth[s]
vector<pair<int, int>> event1[MAXN];
// 第二类事件：处理 lca -> t 这一段（不含 lca），key = depth[s] - 2 * depth[lca] + offset
vector<pair<int, int>> event2[MAXN];

// 当前“已完成后序统计的子树”里，两类 key 的出现次数。
vector<int> cnt1;
vector<int> cnt2;
// 第二类 key 可能为负，整体平移后再开桶统计。
int offset_value;
int bucket_limit;

int answer[MAXN];

void init_tree(int n) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        event1[i].clear();
        event2[i].clear();
        parent_arr[i] = 0;
        depth_arr[i] = 0;
        iter_idx[i] = 0;
        answer[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
        }
    }
}

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// 非递归建树，顺便预处理父亲和倍增祖先表。
// 题目提示可能栈溢出，所以这里不用递归 DFS。
void build_lca() {
    vector<int> st;
    st.push_back(1);
    parent_arr[1] = 0;
    depth_arr[1] = 0;
    for (int j = 0; j < LOG; j++) {
        up[1][j] = 1;
    }

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }

            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < LOG; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }

            st.push_back(v);
        }
    }
}

int kth_ancestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    return u;
}

int lca(int a, int b) {
    if (depth_arr[a] < depth_arr[b]) {
        swap(a, b);
    }

    a = kth_ancestor(a, depth_arr[a] - depth_arr[b]);
    if (a == b) {
        return a;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

void add_event(vector<pair<int, int>> events[], int node, int key, int delta) {
    if (0 <= key && key <= bucket_limit) {
        events[node].push_back(make_pair(key, delta));
    }
}

void solve() {
    // 第一类 key 最大不超过 n，第二类 key 平移后也能落在 [0, 2n] 里。
    bucket_limit = 2 * n + 5;
    offset_value = n + 2;
    cnt1.assign(bucket_limit + 1, 0);
    cnt2.assign(bucket_limit + 1, 0);

    for (int i = 1; i <= m; i++) {
        int s, t;
        cin >> s >> t;

        int p = lca(s, t);

        // 把一条路径 s -> t 拆成两段：
        // 1. s -> lca(s, t)
        // 2. lca(s, t) -> t（不含 lca）
        //
        // 对于第一段，u 被看到的条件是：
        // depth[s] - depth[u] == w[u]
        // 也就是 depth[s] == depth[u] + w[u]
        add_event(event1, s, depth_arr[s], 1);
        if (p != 1) {
            // 在 parent(lca) 处挂 -1，表示上升段到 lca 为止。
            add_event(event1, parent_arr[p], depth_arr[s], -1);
        }

        // 对于第二段，u 被看到的条件是：
        // depth[s] - 2 * depth[lca] + depth[u] == w[u]
        // 也就是 depth[s] - 2 * depth[lca] == w[u] - depth[u]
        //
        // 这里把左边这一项作为第二类 key。
        int key = depth_arr[s] - 2 * depth_arr[p] + offset_value;
        add_event(event2, t, key, 1);
        // 第二段不包含 lca，所以在 lca 本身挂 -1。
        add_event(event2, p, key, -1);
    }

    vector<Frame> st;
    int key1_root = depth_arr[1] + w[1];
    int key2_root = w[1] - depth_arr[1] + offset_value;
    st.push_back({1, (0 <= key1_root && key1_root <= bucket_limit) ? cnt1[key1_root] : 0,
                  (0 <= key2_root && key2_root <= bucket_limit) ? cnt2[key2_root] : 0});

    // 显式栈模拟后序 DFS。
    // before1 / before2 记录“进入 u 子树前”桶中目标 key 的值。
    // 退出 u 时再读取一次，二者差值就是整棵子树给 u 带来的贡献。
    while (!st.empty()) {
        int u = st.back().u;

        if (iter_idx[u] < (int)g[u].size()) {
            int v = g[u][iter_idx[u]++];
            if (v == parent_arr[u]) {
                continue;
            }

            int key1 = depth_arr[v] + w[v];
            int key2 = w[v] - depth_arr[v] + offset_value;
            int before1 = (0 <= key1 && key1 <= bucket_limit) ? cnt1[key1] : 0;
            int before2 = (0 <= key2 && key2 <= bucket_limit) ? cnt2[key2] : 0;
            st.push_back({v, before1, before2});
        }
        else {
            // 所有孩子都处理完后，再把挂在 u 上的事件加入桶。
            for (size_t i = 0; i < event1[u].size(); i++) {
                cnt1[event1[u][i].first] += event1[u][i].second;
            }
            for (size_t i = 0; i < event2[u].size(); i++) {
                cnt2[event2[u][i].first] += event2[u][i].second;
            }

            int key1 = depth_arr[u] + w[u];
            int key2 = w[u] - depth_arr[u] + offset_value;
            int cur1 = (0 <= key1 && key1 <= bucket_limit) ? cnt1[key1] : 0;
            int cur2 = (0 <= key2 && key2 <= bucket_limit) ? cnt2[key2] : 0;

            // 两次读数的差值，正好是“u 子树中能对 u 产生贡献的路径数量”。
            answer[u] = (cur1 - st.back().before1) + (cur2 - st.back().before2);
            st.pop_back();
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_tree(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build_lca();

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    solve();

    return 0;
}
