#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXNODE = MAXN * 25;

int n, m;
int a[MAXN], sorted_value[MAXN];
int root[MAXN];
int left_child[MAXNODE], right_child[MAXNODE], tree_count[MAXNODE];
int node_count;

int get_rank_value(int x) {
    return lower_bound(sorted_value + 1, sorted_value + n + 1, x) - sorted_value;
}

int build(int l, int r) {
    int p = ++node_count;
    if (l == r) {
        return p;
    }
    int mid = (l + r) / 2;
    left_child[p] = build(l, mid);
    right_child[p] = build(mid + 1, r);
    return p;
}

int update(int old_root, int l, int r, int pos) {
    int p = ++node_count;
    left_child[p] = left_child[old_root];
    right_child[p] = right_child[old_root];
    tree_count[p] = tree_count[old_root] + 1;

    if (l == r) {
        return p;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        left_child[p] = update(left_child[old_root], l, mid, pos);
    } else {
        right_child[p] = update(right_child[old_root], mid + 1, r, pos);
    }
    return p;
}

int query_kth(int left_root, int right_root, int l, int r, int k) {
    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    int left_count = tree_count[left_child[right_root]] - tree_count[left_child[left_root]];
    if (k <= left_count) {
        return query_kth(left_child[left_root], left_child[right_root], l, mid, k);
    }
    return query_kth(right_child[left_root], right_child[right_root], mid + 1, r, k - left_count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sorted_value[i] = a[i];
    }
    sort(sorted_value + 1, sorted_value + n + 1);
    int value_count = unique(sorted_value + 1, sorted_value + n + 1) - sorted_value - 1;

    root[0] = build(1, value_count);
    for (int i = 1; i <= n; i++) {
        int pos = lower_bound(sorted_value + 1, sorted_value + value_count + 1, a[i]) - sorted_value;
        root[i] = update(root[i - 1], 1, value_count, pos);
    }

    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int rank_pos = query_kth(root[l - 1], root[r], 1, value_count, k);
        cout << sorted_value[rank_pos] << '\n';
    }

    return 0;
}
