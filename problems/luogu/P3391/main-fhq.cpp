/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-14 19:06
 * update_at: 2026-09-14 19:06
 */
#include <bits/stdc++.h>
using namespace std;

// 隐式 FHQ-Treap：中序遍历顺序就是当前序列顺序，split 按元素个数分裂。

const int MAXN = 100000 + 5;

struct Node {
    int l, r;
    int size;
    unsigned int fix;
    int val;
    bool rev;
} tr[MAXN];

int n, m;
int root, node_count;
mt19937 rng(233);

int get_size(int u) {
    return tr[u].size;
}

int new_node(int val) {
    int u = ++node_count;
    tr[u].l = tr[u].r = 0;
    tr[u].size = 1;
    tr[u].fix = rng();
    tr[u].val = val;
    tr[u].rev = false;
    return u;
}

void push_up(int u) {
    tr[u].size = get_size(tr[u].l) + get_size(tr[u].r) + 1;
}

void push_down(int u) {
    if (!u || !tr[u].rev) return;
    swap(tr[u].l, tr[u].r);
    tr[tr[u].l].rev ^= 1;
    tr[tr[u].r].rev ^= 1;
    tr[u].rev = false;
}

// x 包含前 k 个元素，y 包含其余元素。
void split(int u, int k, int &x, int &y) {
    if (!u) {
        x = y = 0;
        return;
    }

    push_down(u);
    if (get_size(tr[u].l) >= k) {
        y = u;
        split(tr[u].l, k, x, tr[y].l);
        push_up(y);
    } else {
        x = u;
        split(tr[u].r, k - get_size(tr[u].l) - 1, tr[x].r, y);
        push_up(x);
    }
}

// 合并两段相邻序列：x 的全部元素排在 y 的前面。
int merge(int x, int y) {
    if (!x || !y) return x + y;

    if (tr[x].fix > tr[y].fix) {
        push_down(x);
        tr[x].r = merge(tr[x].r, y);
        push_up(x);
        return x;
    }

    push_down(y);
    tr[y].l = merge(x, tr[y].l);
    push_up(y);
    return y;
}

void reverse_range(int l, int r) {
    int left_part, middle_part, right_part;
    split(root, r, left_part, right_part);
    split(left_part, l - 1, left_part, middle_part);

    // 只翻转中段根的左右儿子，真正访问子树时再下传。
    tr[middle_part].rev ^= 1;
    root = merge(merge(left_part, middle_part), right_part);
}

void output(int u, bool &first) {
    if (!u) return;
    push_down(u);
    output(tr[u].l, first);
    if (!first) cout << ' ';
    cout << tr[u].val;
    first = false;
    output(tr[u].r, first);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        root = merge(root, new_node(i));
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        reverse_range(l, r);
    }

    bool first = true;
    output(root, first);
    cout << '\n';
    return 0;
}
