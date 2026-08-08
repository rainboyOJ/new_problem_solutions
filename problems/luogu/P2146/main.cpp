#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
int head[MAXN], to[MAXN], nxt[MAXN], edge_cnt;
int parent_arr[MAXN], depth_arr[MAXN];
int sub_size[MAXN], heavy_son[MAXN];
int top_arr[MAXN], dfn[MAXN], rev_dfn[MAXN], dfs_clock;
int seg_sum[MAXN << 2];
int lazy_tag[MAXN << 2];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void build_tree_info() {
    static int order[MAXN];
    static int stk[MAXN];

    int ord_cnt = 0;
    int top = 0;
    stk[++top] = 0;
    parent_arr[0] = -1;
    depth_arr[0] = 1;

    while (top > 0) {
        int u = stk[top--];
        order[++ord_cnt] = u;
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            stk[++top] = v;
        }
    }

    for (int idx = ord_cnt; idx >= 1; idx--) {
        int u = order[idx];
        sub_size[u] = 1;
        heavy_son[u] = -1;
        int best_size = 0;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            sub_size[u] += sub_size[v];
            if (sub_size[v] > best_size) {
                best_size = sub_size[v];
                heavy_son[u] = v;
            }
        }
    }
}

void build_dfn() {
    static int stk_u[MAXN];
    static int stk_top[MAXN];

    int top = 0;
    stk_u[++top] = 0;
    stk_top[top] = 0;

    while (top > 0) {
        int u = stk_u[top];
        int chain_top = stk_top[top];
        top--;

        while (u != -1) {
            top_arr[u] = chain_top;
            dfn[u] = ++dfs_clock;
            rev_dfn[dfs_clock] = u;

            for (int i = head[u]; i != 0; i = nxt[i]) {
                int v = to[i];
                if (v == heavy_son[u]) {
                    continue;
                }
                stk_u[++top] = v;
                stk_top[top] = v;
            }

            u = heavy_son[u];
        }
    }
}

void build_seg(int u, int l, int r) {
    seg_sum[u] = 0;
    lazy_tag[u] = -1;
    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    build_seg(u << 1, l, mid);
    build_seg(u << 1 | 1, mid + 1, r);
}

void apply_set(int u, int l, int r, int val) {
    seg_sum[u] = (r - l + 1) * val;
    lazy_tag[u] = val;
}

void push_down(int u, int l, int r) {
    if (lazy_tag[u] == -1 || l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    apply_set(u << 1, l, mid, lazy_tag[u]);
    apply_set(u << 1 | 1, mid + 1, r, lazy_tag[u]);
    lazy_tag[u] = -1;
}

void push_up(int u) {
    seg_sum[u] = seg_sum[u << 1] + seg_sum[u << 1 | 1];
}

void range_set(int u, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        apply_set(u, l, r, val);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_set(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        range_set(u << 1 | 1, mid + 1, r, ql, qr, val);
    }
    push_up(u);
}

int query_sum(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg_sum[u];
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans += query_sum(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        ans += query_sum(u << 1 | 1, mid + 1, r, ql, qr);
    }
    return ans;
}

int query_path_sum(int u, int v) {
    int ans = 0;
    while (top_arr[u] != top_arr[v]) {
        if (depth_arr[top_arr[u]] < depth_arr[top_arr[v]]) {
            swap(u, v);
        }
        ans += query_sum(1, 1, n, dfn[top_arr[u]], dfn[u]);
        u = parent_arr[top_arr[u]];
    }

    if (depth_arr[u] > depth_arr[v]) {
        swap(u, v);
    }
    ans += query_sum(1, 1, n, dfn[u], dfn[v]);
    return ans;
}

void set_path(int u, int v, int val) {
    while (top_arr[u] != top_arr[v]) {
        if (depth_arr[top_arr[u]] < depth_arr[top_arr[v]]) {
            swap(u, v);
        }
        range_set(1, 1, n, dfn[top_arr[u]], dfn[u], val);
        u = parent_arr[top_arr[u]];
    }

    if (depth_arr[u] > depth_arr[v]) {
        swap(u, v);
    }
    range_set(1, 1, n, dfn[u], dfn[v], val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        add_edge(p, i);
    }

    build_tree_info();
    build_dfn();
    build_seg(1, 1, n);

    int q;
    cin >> q;
    while (q--) {
        string op;
        int x;
        cin >> op >> x;

        if (op[0] == 'i') {
            // 安装 x，相当于把根到 x 的整条依赖链全部设为 1。
            int installed_before = query_path_sum(0, x);
            int changed = depth_arr[x] - installed_before;
            set_path(0, x, 1);
            cout << changed << '\n';
        } else {
            // 卸载 x，相当于把 x 的整棵子树全部设为 0。
            int l = dfn[x];
            int r = dfn[x] + sub_size[x] - 1;
            int installed_before = query_sum(1, 1, n, l, r);
            range_set(1, 1, n, l, r, 0);
            cout << installed_before << '\n';
        }
    }

    return 0;
}
