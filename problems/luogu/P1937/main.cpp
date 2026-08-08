#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int INF = 0x3f3f3f3f;

struct Request {
    int l, r;
};

int n, m;
int cap[MAXN];
Request req[MAXN];
int seg_min[MAXN << 2];
int lazy_add[MAXN << 2];

bool cmp_req(const Request &a, const Request &b) {
    if (a.r != b.r) {
        return a.r < b.r;
    }
    return a.l > b.l;
}

void push_up(int u) {
    seg_min[u] = min(seg_min[u << 1], seg_min[u << 1 | 1]);
}

void build(int u, int l, int r) {
    lazy_add[u] = 0;
    if (l == r) {
        seg_min[u] = cap[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}

void apply_add(int u, int val) {
    seg_min[u] += val;
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

int query_min(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg_min[u];
    }

    push_down(u);
    int mid = (l + r) >> 1;
    int ans = INF;
    if (ql <= mid) {
        ans = min(ans, query_min(u << 1, l, mid, ql, qr));
    }
    if (qr > mid) {
        ans = min(ans, query_min(u << 1 | 1, mid + 1, r, ql, qr));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> cap[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> req[i].l >> req[i].r;
    }

    sort(req + 1, req + m + 1, cmp_req);
    build(1, 1, n);

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        // 若整段区间的最小剩余容量还大于 0，
        // 说明这头牛的请求还能整体接下。
        if (query_min(1, 1, n, req[i].l, req[i].r) > 0) {
            ans++;
            range_add(1, 1, n, req[i].l, req[i].r, -1);
        }
    }

    cout << ans << '\n';
    return 0;
}
