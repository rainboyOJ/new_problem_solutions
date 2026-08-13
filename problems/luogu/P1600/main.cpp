/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 23:01
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300000 + 5;
const int LOG = 20;  // 2^19 > 3e5，20 层倍增足够

int n, m;
vector<int> g[MAXN];  // 树的邻接表
int w[MAXN];          // w[u]：u 点观察员的观察时刻

int depth_arr[MAXN];       // depth_arr[u]：u 的深度，根 1 的深度为 0
int up[MAXN][LOG];         // up[u][j]：u 向上跳 2^j 步到达的点

// 第一类事件：上升段 s -> lca 的 (key, delta)
// key = depth[s]，在 s 处 +1，在 parent(lca) 处 -1
vector<pair<int, int>> event_up[MAXN];
// 第二类事件：下降段 lca -> t 的 (key, delta)
// key = depth[s] - 2*depth[lca] + offset，在 t 处 +1，在 lca 处 -1
vector<pair<int, int>> event_down[MAXN];

const int BUCKET_SIZE = 2 * MAXN + 10;  // 两类 key 平移后最大约 2n
int cnt_up[BUCKET_SIZE];                // 第一类 key 的计数桶
int cnt_down[BUCKET_SIZE];              // 第二类 key 的计数桶
int offset_value;                       // 第二类 key 的平移量

int answer[MAXN];  // answer[u]：u 点观察员看到的人数

// 非递归遍历整棵树，预处理深度和倍增祖先表（避免栈溢出）。
void build_lca() {
    vector<int> st;
    st.push_back(1);
    for (int j = 0; j < LOG; j++) {
        up[1][j] = 1;  // 根的祖先是它自己
    }

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == up[u][0]) {
                continue;  // 跳过父亲
            }

            depth_arr[v] = depth_arr[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < LOG; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }
            st.push_back(v);
        }
    }
}

// 求 a 和 b 的最近公共祖先。
int lca(int a, int b) {
    if (depth_arr[a] < depth_arr[b]) {
        swap(a, b);
    }

    // 先把 a 提到和 b 同一深度。
    int diff = depth_arr[a] - depth_arr[b];
    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            a = up[a][j];
        }
    }

    if (a == b) {
        return a;
    }

    // 从大到小尝试一起往上跳，最后跳到的点再往上一步就是 lca。
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

// 往桶里加入一个事件，key 必须落在桶范围内才生效。
void add_to_bucket(int cnt[], int key, int delta) {
    if (0 <= key && key < BUCKET_SIZE) {
        cnt[key] += delta;
    }
}

// 显式栈模拟后序遍历：记录进入每个点子树前两个桶的读数。
struct Frame {
    int u;             // 当前点
    int child_idx;     // 下一个要访问的孩子下标
    int before_up;     // 进入 u 子树前，第一类目标 key 的桶值
    int before_down;   // 进入 u 子树前，第二类目标 key 的桶值
};

void solve() {
    offset_value = n + 2;

    // 把每条玩家路径拆成两段，分别挂事件。
    for (int i = 1; i <= m; i++) {
        int s, t;
        cin >> s >> t;
        int p = lca(s, t);

        // 上升段 s -> lca：u 在上升段当且仅当被观察到时满足
        // depth[s] - depth[u] == w[u]，即 depth[s] == depth[u] + w[u]。
        // 在 s 处 +1，在 parent(lca) 处 -1（lca 是根时不用减）。
        event_up[s].push_back(make_pair(depth_arr[s], 1));
        if (p != 1) {
            event_up[up[p][0]].push_back(make_pair(depth_arr[s], -1));
        }

        // 下降段 lca -> t（不含 lca）：u 在下降段当且仅当被观察到时满足
        // depth[s] - 2*depth[lca] + depth[u] == w[u]，
        // 即 depth[s] - 2*depth[lca] == w[u] - depth[u]。
        // key 可能为负，整体平移 offset_value 后再入桶。
        int key = depth_arr[s] - 2 * depth_arr[p] + offset_value;
        event_down[t].push_back(make_pair(key, 1));
        event_down[p].push_back(make_pair(key, -1));
    }

    // 显式栈做后序遍历：进入点 u 前记下桶值，处理完 u 的整棵子树后
    // 再读一次桶值，两者的差就是 u 子树对 u 的贡献。
    vector<Frame> st;
    Frame root_frame;
    root_frame.u = 1;
    root_frame.child_idx = 0;
    root_frame.before_up = cnt_up[depth_arr[1] + w[1]];
    root_frame.before_down = cnt_down[w[1] - depth_arr[1] + offset_value];
    st.push_back(root_frame);

    while (!st.empty()) {
        int u = st.back().u;
        int child_idx = st.back().child_idx;

        if (child_idx < (int)g[u].size()) {
            // 遍历 u 的下一个孩子 v。
            st.back().child_idx++;
            int v = g[u][child_idx];
            if (v == up[u][0]) {
                continue;  // 跳过父亲
            }

            Frame child_frame;
            child_frame.u = v;
            child_frame.child_idx = 0;
            child_frame.before_up = cnt_up[depth_arr[v] + w[v]];
            child_frame.before_down = cnt_down[w[v] - depth_arr[v] + offset_value];
            st.push_back(child_frame);
        } else {
            // u 的所有孩子都处理完：先把挂在 u 上的事件加入桶。
            for (size_t i = 0; i < event_up[u].size(); i++) {
                add_to_bucket(cnt_up, event_up[u][i].first, event_up[u][i].second);
            }
            for (size_t i = 0; i < event_down[u].size(); i++) {
                add_to_bucket(cnt_down, event_down[u][i].first, event_down[u][i].second);
            }

            // 目标 key：depth[u] + w[u] 与 w[u] - depth[u] + offset。
            int cur_up = cnt_up[depth_arr[u] + w[u]];
            int cur_down = cnt_down[w[u] - depth_arr[u] + offset_value];
            answer[u] = (cur_up - st.back().before_up) + (cur_down - st.back().before_down);
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
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    build_lca();
    solve();

    return 0;
}
