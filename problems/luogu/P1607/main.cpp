#include <bits/stdc++.h>
using namespace std;

const int MAXK = 50000 + 5;
const int MAXN = 20000 + 5;

struct Order {
    int s, e, m;
};

int req_cnt, stop_cnt, cap;
Order ord[MAXK];
int seg_max[MAXN << 2];
int lazy_add[MAXN << 2];

bool cmp_order(const Order &a, const Order &b) {
    if (a.e != b.e) {
        return a.e < b.e;
    }
    // 同终点时，起点更大的请求更短，应该优先处理。
    return a.s > b.s;
}

void push_up(int u) {
    seg_max[u] = max(seg_max[u << 1], seg_max[u << 1 | 1]);
}

void apply_add(int u, int val) {
    seg_max[u] += val;
    lazy_add[u] += val;
}

void push_down(int u) {
    if (lazy_add[u] == 0) {
        return;
    }
    apply_add(u << 1, lazy_add[u]);
    apply_add(u << 1 | 1, lazy_add[u]);
    lazy_add[u] = 0;
}

void range_add(int u, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        apply_add(u, val);
        return;
    }

    push_down(u);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_add(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        range_add(u << 1 | 1, mid + 1, r, ql, qr, val);
    }
    push_up(u);
}

int query_max(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg_max[u];
    }

    push_down(u);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans = max(ans, query_max(u << 1, l, mid, ql, qr));
    }
    if (qr > mid) {
        ans = max(ans, query_max(u << 1 | 1, mid + 1, r, ql, qr));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> req_cnt >> stop_cnt >> cap;
    for (int i = 1; i <= req_cnt; i++) {
        cin >> ord[i].s >> ord[i].e >> ord[i].m;
    }

    sort(ord + 1, ord + req_cnt + 1, cmp_order);

    long long ans = 0;
    for (int i = 1; i <= req_cnt; i++) {
        int l = ord[i].s;
        int r = ord[i].e - 1;

        // 每个请求会同时占用 [s, e-1] 上的所有路段。
        // 还能再塞多少头牛，只取决于这段区间里最满的那一段。
        int cur_max = query_max(1, 1, stop_cnt - 1, l, r);
        int can_take = min(ord[i].m, cap - cur_max);
        if (can_take <= 0) {
            continue;
        }

        ans += can_take;
        range_add(1, 1, stop_cnt - 1, l, r, can_take);
    }

    cout << ans << '\n';
    return 0;
}
