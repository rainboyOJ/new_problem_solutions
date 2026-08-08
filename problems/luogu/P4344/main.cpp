#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

struct NodeInfo {
    int len;
    int one_cnt;
    int pre_zero;
    int suf_zero;
    int best_zero;
};

int n, m;
int one_cnt[MAXN << 2];
int pre_zero[MAXN << 2];
int suf_zero[MAXN << 2];
int best_zero[MAXN << 2];
int lazy_tag[MAXN << 2];

NodeInfo merge_info(const NodeInfo &left_info, const NodeInfo &right_info) {
    if (left_info.len == 0) {
        return right_info;
    }
    if (right_info.len == 0) {
        return left_info;
    }

    NodeInfo res;
    res.len = left_info.len + right_info.len;
    res.one_cnt = left_info.one_cnt + right_info.one_cnt;

    res.pre_zero = left_info.pre_zero;
    if (left_info.pre_zero == left_info.len) {
        res.pre_zero = left_info.len + right_info.pre_zero;
    }

    res.suf_zero = right_info.suf_zero;
    if (right_info.suf_zero == right_info.len) {
        res.suf_zero = right_info.len + left_info.suf_zero;
    }

    res.best_zero = max(left_info.best_zero, right_info.best_zero);
    res.best_zero = max(res.best_zero, left_info.suf_zero + right_info.pre_zero);
    return res;
}

void apply_set(int u, int l, int r, int val) {
    lazy_tag[u] = val;
    if (val == 0) {
        one_cnt[u] = 0;
        pre_zero[u] = r - l + 1;
        suf_zero[u] = r - l + 1;
        best_zero[u] = r - l + 1;
    } else {
        one_cnt[u] = r - l + 1;
        pre_zero[u] = 0;
        suf_zero[u] = 0;
        best_zero[u] = 0;
    }
}

void push_up(int u, int l, int r) {
    int mid = (l + r) >> 1;
    NodeInfo left_info;
    left_info.len = mid - l + 1;
    left_info.one_cnt = one_cnt[u << 1];
    left_info.pre_zero = pre_zero[u << 1];
    left_info.suf_zero = suf_zero[u << 1];
    left_info.best_zero = best_zero[u << 1];

    NodeInfo right_info;
    right_info.len = r - mid;
    right_info.one_cnt = one_cnt[u << 1 | 1];
    right_info.pre_zero = pre_zero[u << 1 | 1];
    right_info.suf_zero = suf_zero[u << 1 | 1];
    right_info.best_zero = best_zero[u << 1 | 1];

    NodeInfo res = merge_info(left_info, right_info);
    one_cnt[u] = res.one_cnt;
    pre_zero[u] = res.pre_zero;
    suf_zero[u] = res.suf_zero;
    best_zero[u] = res.best_zero;
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

void build(int u, int l, int r) {
    lazy_tag[u] = -1;
    if (l == r) {
        // 初始时所有位置都正常工作，也就是全是 1。
        apply_set(u, l, r, 1);
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u, l, r);
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
    push_up(u, l, r);
}

NodeInfo query_info(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        NodeInfo res;
        res.len = r - l + 1;
        res.one_cnt = one_cnt[u];
        res.pre_zero = pre_zero[u];
        res.suf_zero = suf_zero[u];
        res.best_zero = best_zero[u];
        return res;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (qr <= mid) {
        return query_info(u << 1, l, mid, ql, qr);
    }
    if (ql > mid) {
        return query_info(u << 1 | 1, mid + 1, r, ql, qr);
    }

    NodeInfo left_info = query_info(u << 1, l, mid, ql, qr);
    NodeInfo right_info = query_info(u << 1 | 1, mid + 1, r, ql, qr);
    return merge_info(left_info, right_info);
}

void fill_leftmost_zero(int u, int l, int r, int ql, int qr, int &need) {
    if (need == 0 || qr < l || r < ql) {
        return;
    }

    int zero_cnt = (r - l + 1) - one_cnt[u];
    if (zero_cnt == 0) {
        return;
    }

    if (ql <= l && r <= qr && zero_cnt <= need) {
        apply_set(u, l, r, 1);
        need -= zero_cnt;
        return;
    }

    if (l == r) {
        apply_set(u, l, r, 1);
        need--;
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        fill_leftmost_zero(u << 1, l, mid, ql, qr, need);
    }
    if (qr > mid && need > 0) {
        fill_leftmost_zero(u << 1 | 1, mid + 1, r, ql, qr, need);
    }
    push_up(u, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    build(1, 1, n);

    while (m--) {
        int op;
        cin >> op;

        if (op == 0) {
            int l, r;
            cin >> l >> r;
            range_set(1, 1, n, l, r, 0);
        } else if (op == 1) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            NodeInfo source_info = query_info(1, 1, n, x1, y1);
            int healthy_cnt = source_info.one_cnt;

            // 先把供体区间全部挖空，再把这些 1 从左到右填到目标区间的脑洞里。
            range_set(1, 1, n, x1, y1, 0);
            fill_leftmost_zero(1, 1, n, x2, y2, healthy_cnt);
        } else {
            int l, r;
            cin >> l >> r;
            NodeInfo ans = query_info(1, 1, n, l, r);
            cout << ans.best_zero << '\n';
        }
    }

    return 0;
}
