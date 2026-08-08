#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
const int INF = 1000000000;

int n, q;
int pos_arr[MAXN];
int color_arr[MAXN];
int black_idx[MAXN];
int black_cnt;

int seg_min[MAXN << 2];
int lazy_add[MAXN << 2];
int base_gap[MAXN];

int op_l[MAXN];
int op_r[MAXN];
int op_valid[MAXN];

void push_up(int u) {
    seg_min[u] = min(seg_min[u << 1], seg_min[u << 1 | 1]);
}

void build(int u, int l, int r) {
    lazy_add[u] = 0;
    if (l == r) {
        seg_min[u] = base_gap[l];
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

bool can_all_black() {
    if (color_arr[1] == 0 || color_arr[n] == 0) {
        return false;
    }
    if (black_cnt <= 1) {
        return n == 1 && color_arr[1] == 1;
    }
    return seg_min[1] > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> pos_arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> color_arr[i];
    }

    black_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (color_arr[i] == 1) {
            black_idx[++black_cnt] = i;
        }
    }

    int gap_cnt = max(0, black_cnt - 1);
    if (gap_cnt > 0) {
        for (int i = 1; i <= gap_cnt; i++) {
            if (black_idx[i + 1] == black_idx[i] + 1) {
                // 两个黑点相邻，中间没有白点，这个“缝隙”天然已经满足。
                base_gap[i] = INF;
            } else {
                // 中间存在白点，需要至少一个活跃操作跨过这段缝隙。
                base_gap[i] = 0;
            }
        }
        build(1, 1, gap_cnt);
    }

    cout << (can_all_black() ? "Yes" : "No") << '\n';

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        op_valid[i] = 0;

        if (op == 1) {
            int l, r;
            cin >> l >> r;

            if (gap_cnt > 0) {
                int left_pos = lower_bound(pos_arr + 1, pos_arr + n + 1, l) - pos_arr;
                int right_pos = (int)(upper_bound(pos_arr + 1, pos_arr + n + 1, r) - pos_arr) - 1;

                if (left_pos <= right_pos && black_cnt >= 2) {
                    int left_black = lower_bound(black_idx + 1, black_idx + black_cnt + 1, left_pos) - black_idx;
                    int right_black = (int)(upper_bound(black_idx + 1, black_idx + black_cnt + 1, right_pos) - black_idx) - 1;

                    if (left_black < right_black) {
                        op_valid[i] = 1;
                        op_l[i] = left_black;
                        op_r[i] = right_black - 1;
                        range_add(1, 1, gap_cnt, op_l[i], op_r[i], 1);
                    }
                }
            }
        } else {
            int x;
            cin >> x;
            if (gap_cnt > 0 && op_valid[x]) {
                range_add(1, 1, gap_cnt, op_l[x], op_r[x], -1);
            }
        }

        cout << (can_all_black() ? "Yes" : "No") << '\n';
    }

    return 0;
}
