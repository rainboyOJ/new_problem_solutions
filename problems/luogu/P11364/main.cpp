#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int LOG = 20;

struct Edge {
    int to;
    int next;
};

struct SegNode {
    int len;
    int pref;
    int suf;
    int best;
};

struct Query {
    int left;
    int right;
    int need;
    int id;
};

int n, q;
int head[MAXN], edge_cnt;
Edge edges[MAXN * 2];
int depth_node[MAXN];
int up[LOG][MAXN];
int adjacent_depth[MAXN];
int depth_log[MAXN];
int depth_st[LOG][MAXN];
int answer[MAXN];

vector<int> values;
int value_id[MAXN];
int position_order[MAXN];
vector<Query> queries;

SegNode seg[MAXN * 4];
int low_bound_idx[MAXN], high_bound_idx[MAXN], answer_idx[MAXN];
int bucket_head[MAXN], bucket_next[MAXN];
vector<int> used_bucket;

void add_edge(int u, int v) {
    edge_cnt++;
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

SegNode merge_node(SegNode a, SegNode b) {
    SegNode c;
    c.len = a.len + b.len;
    c.pref = a.pref;
    if (a.pref == a.len) {
        c.pref = a.len + b.pref;
    }
    c.suf = b.suf;
    if (b.suf == b.len) {
        c.suf = b.len + a.suf;
    }
    c.best = max(max(a.best, b.best), a.suf + b.pref);
    return c;
}

void build_seg(int p, int l, int r) {
    seg[p].len = r - l + 1;
    seg[p].pref = seg[p].suf = seg[p].best = 0;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build_seg(p << 1, l, mid);
    build_seg(p << 1 | 1, mid + 1, r);
}

void reset_seg(int p, int l, int r) {
    seg[p].pref = seg[p].suf = seg[p].best = 0;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    reset_seg(p << 1, l, mid);
    reset_seg(p << 1 | 1, mid + 1, r);
}

void activate_position(int p, int l, int r, int pos) {
    if (l == r) {
        seg[p].pref = seg[p].suf = seg[p].best = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        activate_position(p << 1, l, mid, pos);
    } else {
        activate_position(p << 1 | 1, mid + 1, r, pos);
    }
    seg[p] = merge_node(seg[p << 1], seg[p << 1 | 1]);
}

SegNode query_seg(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg[p];
    }
    int mid = (l + r) >> 1;
    if (qr <= mid) {
        return query_seg(p << 1, l, mid, ql, qr);
    }
    if (ql > mid) {
        return query_seg(p << 1 | 1, mid + 1, r, ql, qr);
    }
    SegNode left_node = query_seg(p << 1, l, mid, ql, qr);
    SegNode right_node = query_seg(p << 1 | 1, mid + 1, r, ql, qr);
    return merge_node(left_node, right_node);
}

void build_lca() {
    vector<int> order;
    order.push_back(1);
    up[0][1] = 0;
    depth_node[1] = 1;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int e = head[u]; e != 0; e = edges[e].next) {
            int v = edges[e].to;
            if (v == up[0][u]) {
                continue;
            }
            up[0][v] = u;
            depth_node[v] = depth_node[u] + 1;
            order.push_back(v);
        }
    }

    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[j][i] = up[j - 1][up[j - 1][i]];
        }
    }
}

int lca(int u, int v) {
    if (depth_node[u] < depth_node[v]) {
        swap(u, v);
    }
    int diff = depth_node[u] - depth_node[v];
    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            u = up[j][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }
    return up[0][u];
}

void build_depth_rmq() {
    for (int i = 2; i <= n; i++) {
        depth_log[i] = depth_log[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        depth_st[0][i] = depth_node[i];
    }
    for (int j = 1; j < LOG; j++) {
        int len = 1 << j;
        for (int i = 1; i + len - 1 <= n; i++) {
            depth_st[j][i] = max(depth_st[j - 1][i], depth_st[j - 1][i + (len >> 1)]);
        }
    }
}

int query_depth_max(int l, int r) {
    int len = r - l + 1;
    int lg = depth_log[len];
    return max(depth_st[lg][l], depth_st[lg][r - (1 << lg) + 1]);
}

bool cmp_position_by_value(int a, int b) {
    if (value_id[a] != value_id[b]) {
        return value_id[a] > value_id[b];
    }
    return a < b;
}

void solve_parallel_binary_search() {
    int total_values = (int)values.size();
    int total_queries = (int)queries.size();
    if (total_queries == 0) {
        return;
    }

    for (int i = 0; i < total_queries; i++) {
        low_bound_idx[i] = 0;
        high_bound_idx[i] = total_values - 1;
        answer_idx[i] = 0;
    }

    int edge_count = n - 1;
    for (int i = 1; i <= edge_count; i++) {
        position_order[i] = i;
    }
    sort(position_order + 1, position_order + edge_count + 1, cmp_position_by_value);

    build_seg(1, 1, edge_count);

    bool changed = true;
    while (changed) {
        changed = false;
        used_bucket.clear();

        for (int i = 0; i < total_queries; i++) {
            if (low_bound_idx[i] <= high_bound_idx[i]) {
                changed = true;
                int mid = (low_bound_idx[i] + high_bound_idx[i]) >> 1;
                if (bucket_head[mid] == -1) {
                    used_bucket.push_back(mid);
                }
                bucket_next[i] = bucket_head[mid];
                bucket_head[mid] = i;
            }
        }

        if (!changed) {
            break;
        }

        reset_seg(1, 1, edge_count);
        int ptr = 1;

        for (int value_index = total_values - 1; value_index >= 0; value_index--) {
            while (ptr <= edge_count && value_id[position_order[ptr]] >= value_index) {
                activate_position(1, 1, edge_count, position_order[ptr]);
                ptr++;
            }

            for (int idx = bucket_head[value_index]; idx != -1; idx = bucket_next[idx]) {
                Query qu = queries[idx];
                SegNode res = query_seg(1, 1, edge_count, qu.left, qu.right);
                if (res.best >= qu.need) {
                    answer_idx[idx] = value_index;
                    low_bound_idx[idx] = value_index + 1;
                } else {
                    high_bound_idx[idx] = value_index - 1;
                }
            }
        }

        for (int i = 0; i < (int)used_bucket.size(); i++) {
            bucket_head[used_bucket[i]] = -1;
        }
    }

    for (int i = 0; i < total_queries; i++) {
        answer[queries[i].id] = values[answer_idx[i]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    build_lca();
    build_depth_rmq();

    if (n > 1) {
        values.reserve(n - 1);
        for (int i = 1; i < n; i++) {
            adjacent_depth[i] = depth_node[lca(i, i + 1)];
            values.push_back(adjacent_depth[i]);
        }
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        for (int i = 1; i < n; i++) {
            value_id[i] = lower_bound(values.begin(), values.end(), adjacent_depth[i]) - values.begin();
        }
        for (int i = 0; i < (int)values.size(); i++) {
            bucket_head[i] = -1;
        }
    }

    cin >> q;
    for (int id = 1; id <= q; id++) {
        int l, r, k;
        cin >> l >> r >> k;
        if (k == 1) {
            answer[id] = query_depth_max(l, r);
        } else {
            Query qu;
            qu.left = l;
            qu.right = r - 1;
            qu.need = k - 1;
            qu.id = id;
            queries.push_back(qu);
        }
    }

    if (n > 1) {
        solve_parallel_binary_search();
    }

    for (int i = 1; i <= q; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
