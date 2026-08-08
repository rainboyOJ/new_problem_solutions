#include <bits/stdc++.h>
using namespace std;

const int MAXL = 10005;

int L, n;
int empty_cnt[MAXL << 2];   // 当前区间里空地数量
int sapling_cnt[MAXL << 2]; // 当前区间里树苗数量
int tag[MAXL << 2];         // -1 混合，0 全是老树，1 全是空地，2 全是树苗

int removed_saplings; // 被种上后又被砍掉的树苗总数

void apply_tag(int u, int l, int r, int value) {
    tag[u] = value;
    int len = r - l + 1;
    if (value == 0) {
        empty_cnt[u] = 0;
        sapling_cnt[u] = 0;
    } else if (value == 1) {
        empty_cnt[u] = len;
        sapling_cnt[u] = 0;
    } else {
        empty_cnt[u] = 0;
        sapling_cnt[u] = len;
    }
}

void push_up(int u) {
    empty_cnt[u] = empty_cnt[u << 1] + empty_cnt[u << 1 | 1];
    sapling_cnt[u] = sapling_cnt[u << 1] + sapling_cnt[u << 1 | 1];

    if (tag[u << 1] == tag[u << 1 | 1] && tag[u << 1] != -1) {
        tag[u] = tag[u << 1];
    } else {
        tag[u] = -1;
    }
}

void push_down(int u, int l, int r) {
    if (tag[u] == -1 || l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    apply_tag(u << 1, l, mid, tag[u]);
    apply_tag(u << 1 | 1, mid + 1, r, tag[u]);
    tag[u] = -1;
}

void build(int u, int l, int r) {
    // 初始时每个位置都是老树。
    apply_tag(u, l, r, 0);
    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

// 区间砍树：无论老树还是树苗都清空。
void cut_range(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        removed_saplings += sapling_cnt[u];
        apply_tag(u, l, r, 1);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        cut_range(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        cut_range(u << 1 | 1, mid + 1, r, ql, qr);
    }
    push_up(u);
}

// 区间补种：只在空地位置种上树苗。
void plant_range(int u, int l, int r, int ql, int qr) {
    if (empty_cnt[u] == 0) {
        return;
    }
    if (ql <= l && r <= qr && tag[u] == 1) {
        apply_tag(u, l, r, 2);
        return;
    }
    if (l == r) {
        apply_tag(u, l, r, 2);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        plant_range(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        plant_range(u << 1 | 1, mid + 1, r, ql, qr);
    }
    push_up(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> n;
    build(1, 0, L);

    for (int i = 1; i <= n; i++) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0) {
            cut_range(1, 0, L, l, r);
        } else {
            plant_range(1, 0, L, l, r);
        }
    }

    cout << sapling_cnt[1] << '\n' << removed_saplings << '\n';
    return 0;
}
