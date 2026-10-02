/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
// main.cpp：k<=3 的树上点权最短路，用重链剖分维护 min-plus 转移矩阵。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;
const int MAXM = 400005;
// 无穷大哨兵：4e18 远大于合法答案上界（n * max(v) <= 2e14），且 2*INF 不溢出。
const ll INF = 4000000000000000000LL;

// k <= 3 的 min-plus 转移矩阵，只用前 K 行前 K 列。
struct Matrix {
    ll a[3][3];
};

// 路径一侧的 DP 状态：a[d] 表示距离上一次选作中转主机的点 d 条边时的最小代价。
struct DpState {
    ll a[3];
};

int n, q, K;
ll val[MAXN];            // val[i]：主机 i 的处理时间（点权）
ll min_neighbor[MAXN];   // min_neighbor[u]：u 的相邻点中最小点权，k=3 时离路径一步的旁路用
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt; // 链式前向星存树
int parent_node[MAXN], depth_node[MAXN], subtree_size[MAXN], heavy_son[MAXN];
int top_node[MAXN], dfn[MAXN], rev_dfn[MAXN], dfn_cnt; // 重链剖分的链顶与 DFS 序
Matrix base_matrix[MAXN];   // base_matrix[u]：从 u 走到父亲的一步转移
Matrix chain_matrix[MAXN];  // chain_matrix[u]：从 u 走到重链链顶父亲的转移乘积
Matrix seg_tree[MAXN * 4];  // 线段树按 DFS 序维护重链内部的矩阵乘积

// 链式前向星加一条 u -> v 的有向边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// min-plus 加法：任一加数达到哨兵量级时结果视为无穷大，避免溢出。
ll safe_add(ll x, ll y) {
    if (x >= INF / 2 || y >= INF / 2) {
        return INF;
    }
    if (x + y >= INF) {
        return INF;
    }
    return x + y;
}

// min-plus 矩阵乘法：result[i][j] = min_k (x[i][k] + y[k][j])。
Matrix multiply_matrix(const Matrix &x, const Matrix &y) {
    Matrix result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.a[i][j] = INF;
        }
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                result.a[i][j] = min(result.a[i][j], safe_add(x.a[i][k], y.a[k][j]));
            }
        }
    }
    return result;
}

// DP 状态右乘转移矩阵：result[i] = min_j (x.a[j] + y[j][i])。
DpState multiply_dp(const DpState &x, const Matrix &y) {
    DpState result;
    for (int i = 0; i < 3; i++) {
        result.a[i] = INF;
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            result.a[i] = min(result.a[i], safe_add(x.a[j], y.a[j][i]));
        }
    }
    return result;
}

// 构造走到某点的一步转移：选它当中转点（状态回 0、加上点权 x）、
// 不选它（距离 +1）；k=3 时还允许经它的最小权邻居旁路（mn）。
Matrix make_transition(ll x, ll mn) {
    Matrix result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.a[i][j] = INF;
        }
    }

    if (K == 1) {
        result.a[0][0] = x;
    } else if (K == 2) {
        result.a[0][0] = x;
        result.a[1][0] = x;
        result.a[0][1] = 0;
    } else {
        result.a[0][0] = x;
        result.a[1][0] = x;
        result.a[2][0] = x;
        result.a[0][1] = 0;
        result.a[1][2] = 0;
        result.a[2][2] = mn;
    }
    return result;
}

// 预处理：父节点/深度/子树大小/重儿子、链顶与 DFS 序、
// min_neighbor、base_matrix 与 chain_matrix（迭代写法避免深树爆栈）。
void build_tree_info() {
    vector<int> order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    parent_node[1] = 0;
    depth_node[1] = 1;

    // 第一遍 DFS 得到父节点、深度与遍历顺序。
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            depth_node[v] = depth_node[u] + 1;
            st.push(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        min_neighbor[i] = INF;
    }
    for (int u = 1; u <= n; u++) {
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            min_neighbor[u] = min(min_neighbor[u], val[v]);
        }
    }

    // 逆序求子树大小与重儿子。
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        subtree_size[u] = 1;
        heavy_son[u] = 0;
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (v == parent_node[u]) {
                continue;
            }
            subtree_size[u] += subtree_size[v];
            if (subtree_size[v] > subtree_size[heavy_son[u]]) {
                heavy_son[u] = v;
            }
        }
    }

    // 按重链分配链顶与 DFS 序。
    stack<pair<int, int> > starts;
    starts.push(make_pair(1, 1));
    while (!starts.empty()) {
        int start = starts.top().first;
        int top = starts.top().second;
        starts.pop();

        int u = start;
        while (u != 0) {
            top_node[u] = top;
            dfn[u] = ++dfn_cnt;
            rev_dfn[dfn_cnt] = u;

            for (int e = head[u]; e != 0; e = nxt[e]) {
                int v = to[e];
                if (v == parent_node[u] || v == heavy_son[u]) {
                    continue;
                }
                starts.push(make_pair(v, v));
            }
            u = heavy_son[u];
        }
    }

    // 按 DFS 序（父先子后）构建一步转移与链上乘积。
    for (int i = 1; i <= n; i++) {
        int u = order[i - 1];
        ll parent_value = (parent_node[u] == 0) ? INF : val[parent_node[u]];
        base_matrix[u] = make_transition(parent_value, min_neighbor[u]);
        if (u == top_node[u]) {
            chain_matrix[u] = base_matrix[u];
        } else {
            chain_matrix[u] = multiply_matrix(base_matrix[u], chain_matrix[parent_node[u]]);
        }
    }
}

// 由 DFS 序区间 [l, r] 构建线段树，叶子是 base_matrix，区间值是矩阵乘积。
void build_segment_tree(int node, int l, int r) {
    if (l == r) {
        seg_tree[node] = base_matrix[rev_dfn[l]];
        return;
    }
    int mid = (l + r) / 2;
    build_segment_tree(node * 2, l, mid);
    build_segment_tree(node * 2 + 1, mid + 1, r);
    seg_tree[node] = multiply_matrix(seg_tree[node * 2 + 1], seg_tree[node * 2]);
}

// 查询 DFS 序区间 [ql, qr] 的矩阵乘积（下标大的先乘，对应先走到的父亲）。
Matrix query_segment_tree(int ql, int qr, int node, int l, int r) {
    if (ql <= l && r <= qr) {
        return seg_tree[node];
    }
    int mid = (l + r) / 2;
    if (qr <= mid) {
        return query_segment_tree(ql, qr, node * 2, l, mid);
    }
    if (ql > mid) {
        return query_segment_tree(ql, qr, node * 2 + 1, mid + 1, r);
    }
    Matrix right_part = query_segment_tree(ql, qr, node * 2 + 1, mid + 1, r);
    Matrix left_part = query_segment_tree(ql, qr, node * 2, l, mid);
    return multiply_matrix(right_part, left_part);
}

// 求 s=u 到 t=v 的最小总代价：两侧状态向 LCA 收缩后在 LCA 处合并。
ll solve_query(int u, int v) {
    if (u == v) {
        return val[u];
    }

    DpState left_state, right_state;
    for (int i = 0; i < 3; i++) {
        left_state.a[i] = right_state.a[i] = INF;
    }
    left_state.a[0] = val[u];
    right_state.a[0] = val[v];

    // 先把较深的一侧沿重链向上收缩，直到两点同链。
    while (top_node[u] != top_node[v]) {
        if (depth_node[top_node[u]] < depth_node[top_node[v]]) {
            swap(u, v);
            swap(left_state, right_state);
        }
        left_state = multiply_dp(left_state, chain_matrix[u]);
        u = parent_node[top_node[u]];
    }

    if (depth_node[u] > depth_node[v]) {
        swap(u, v);
        swap(left_state, right_state);
    }

    // 同链后 u 是 LCA；v 一侧还差 (u, v] 这一段，用线段树查询乘积。
    if (u != v) {
        Matrix middle = query_segment_tree(dfn[u] + 1, dfn[v], 1, 1, n);
        right_state = multiply_dp(right_state, middle);
    }

    // 合并两侧：两侧末端距上次中转 i、j 条边，i + j <= K 时可以直接接上。
    // i = j = 0 时 LCA 被算了两次，要减掉一次。
    ll answer = left_state.a[0] + right_state.a[0] - val[u];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (i + j <= K) {
                answer = min(answer, safe_add(left_state.a[i], right_state.a[j]));
            }
        }
    }
    // k=3 时允许在 LCA 处再离路径一步，经它的最小权邻居旁路。
    if (K == 3) {
        answer = min(answer, safe_add(safe_add(left_state.a[2], right_state.a[2]), min_neighbor[u]));
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> K;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    build_tree_info();
    build_segment_tree(1, 1, n);

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << solve_query(u, v) << '\n';
    }

    return 0;
}
