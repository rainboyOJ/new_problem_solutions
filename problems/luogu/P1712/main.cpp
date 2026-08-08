#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
const int MAXP = MAXN << 1;
const int INF = 0x3f3f3f3f;

struct Interval {
    int l, r;
    int len;
};

int n, m;
Interval a[MAXN];
int xs[MAXP];
int xs_cnt;
int seg_max[MAXP << 2];
int lazy_add[MAXP << 2];

bool cmp_len(const Interval &x, const Interval &y) {
    if (x.len != y.len) {
        return x.len < y.len;
    }
    if (x.l != y.l) {
        return x.l < y.l;
    }
    return x.r < y.r;
}

int get_id(int x) {
    return lower_bound(xs + 1, xs + xs_cnt + 1, x) - xs;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].len = a[i].r - a[i].l;
        xs[++xs_cnt] = a[i].l;
        xs[++xs_cnt] = a[i].r;
    }

    sort(xs + 1, xs + xs_cnt + 1);
    xs_cnt = unique(xs + 1, xs + xs_cnt + 1) - (xs + 1);

    for (int i = 1; i <= n; i++) {
        a[i].l = get_id(a[i].l);
        a[i].r = get_id(a[i].r);
    }

    sort(a + 1, a + n + 1, cmp_len);

    int ans = INF;
    int left = 1;
    for (int right = 1; right <= n; right++) {
        // 当前区间加入窗口后，它覆盖的所有坐标点都要 +1。
        range_add(1, 1, xs_cnt, a[right].l, a[right].r, 1);

        // 只要窗口内已经存在某个点被至少 m 个区间覆盖，
        // 就可以尝试收缩左端，更新更小的长度差。
        while (left <= right && seg_max[1] >= m) {
            ans = min(ans, a[right].len - a[left].len);
            range_add(1, 1, xs_cnt, a[left].l, a[left].r, -1);
            left++;
        }
    }

    if (ans == INF) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
