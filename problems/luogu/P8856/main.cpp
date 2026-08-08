#include <bits/stdc++.h>
using namespace std;

const int MAXC = 60000 + 5;

int city_cnt, seat_cnt, req_cnt;
int seg_max[MAXC << 2];
int lazy_add[MAXC << 2];

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

    cin >> city_cnt >> seat_cnt >> req_cnt;
    for (int i = 1; i <= req_cnt; i++) {
        int o, d, n;
        cin >> o >> d >> n;

        // 乘客会占用区间 [o, d-1] 上的每一段铁路。
        int current_max = query_max(1, 1, city_cnt - 1, o, d - 1);
        if (current_max + n <= seat_cnt) {
            cout << "T\n";
            range_add(1, 1, city_cnt - 1, o, d - 1, n);
        } else {
            cout << "N\n";
        }
    }

    return 0;
}
