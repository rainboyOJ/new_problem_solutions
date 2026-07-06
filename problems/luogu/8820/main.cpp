// main.cpp：k<=3 的树上点权最短路，用重链剖分维护 min-plus 转移矩阵。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXM = 400005;
const long long INF = (long long)4e18;

struct Matrix {
    long long a[3][3];
};

struct DpState {
    long long a[3];
};

int n, q, K;
long long val[MAXN], min_neighbor[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int parent_node[MAXN], depth_node[MAXN], subtree_size[MAXN], heavy_son[MAXN];
int top_node[MAXN], dfn[MAXN], rev_dfn[MAXN], dfn_cnt;
Matrix base_matrix[MAXN], chain_matrix[MAXN], seg_tree[MAXN * 4];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

long long safe_add(long long x, long long y) {
    if (x >= INF / 2 || y >= INF / 2) {
        return INF;
    }
    if (x + y >= INF) {
        return INF;
    }
    return x + y;
}

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

Matrix make_transition(long long x, long long mn) {
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

void build_tree_info() {
    vector<int> order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    parent_node[1] = 0;
    depth_node[1] = 1;

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

    for (int i = 1; i <= n; i++) {
        int u = order[i - 1];
        long long parent_value = (parent_node[u] == 0) ? INF : val[parent_node[u]];
        base_matrix[u] = make_transition(parent_value, min_neighbor[u]);
        if (u == top_node[u]) {
            chain_matrix[u] = base_matrix[u];
        } else {
            chain_matrix[u] = multiply_matrix(base_matrix[u], chain_matrix[parent_node[u]]);
        }
    }
}

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

long long solve_query(int u, int v) {
    if (u == v) {
        return val[u];
    }

    DpState left_state, right_state;
    for (int i = 0; i < 3; i++) {
        left_state.a[i] = right_state.a[i] = INF;
    }
    left_state.a[0] = val[u];
    right_state.a[0] = val[v];

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

    if (u != v) {
        Matrix middle = query_segment_tree(dfn[u] + 1, dfn[v], 1, 1, n);
        right_state = multiply_dp(right_state, middle);
    }

    long long answer = left_state.a[0] + right_state.a[0] - val[u];
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
