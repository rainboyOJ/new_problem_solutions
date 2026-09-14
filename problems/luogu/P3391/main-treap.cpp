/*-----------------
* author: Rainboy
* email: rainboylvx@qq.com
* time: 2019年 11月 19日 星期二 15:17:14 CST
* problem: luogu-3391
*----------------*/
#include <bits/stdc++.h>
using namespace std;

// 这里是 Splay 写法；文件名沿用原来的 main-treap.cpp。
const int MAXN = 100000 + 5;

struct Node {
    int fa, ch[2], val, size;
    bool rev;
} spl[MAXN];

int n, m;
int root, node_count;

int get_size(int u) {
    return spl[u].size;
}

void push_up(int u) {
    spl[u].size = get_size(spl[u].ch[0]) + get_size(spl[u].ch[1]) + 1;
}

void push_down(int u) {
    if (!u || !spl[u].rev) return;
    swap(spl[u].ch[0], spl[u].ch[1]);
    spl[spl[u].ch[0]].rev ^= 1;
    spl[spl[u].ch[1]].rev ^= 1;
    spl[u].rev = false;
}

bool ident(int x) {
    return spl[spl[x].fa].ch[1] == x;
}

void connect(int x, int fa, int side) {
    spl[fa].ch[side] = x;
    if (x) spl[x].fa = fa;
}

void rotate(int x) {
    int f = spl[x].fa;
    int ff = spl[f].fa;
    int side = ident(x);

    connect(spl[x].ch[side ^ 1], f, side);
    connect(f, x, side ^ 1);
    connect(x, ff, spl[ff].ch[1] == f);
    push_up(f);
    push_up(x);
}

// 旋转前先把祖先的翻转标记全部下传，避免左右儿子方向过期。
void push_all(int x, int top) {
    if (spl[x].fa != top) push_all(spl[x].fa, top);
    push_down(x);
}

void splay(int x, int top) {
    push_all(x, top);
    while (spl[x].fa != top) {
        int f = spl[x].fa;
        int ff = spl[f].fa;
        if (ff != top) {
            if (ident(x) == ident(f)) rotate(f);
            else rotate(x);
        }
        rotate(x);
    }
    if (!top) root = x;
}

void new_node(int val) {
    int u = ++node_count;
    spl[u].val = val;
    spl[u].size = 1;
    root = u;
}

// 将新元素接到当前序列末尾。
void append(int val) {
    if (!root) {
        new_node(val);
        return;
    }

    int u = root;
    while (spl[u].ch[1]) {
        push_down(u);
        u = spl[u].ch[1];
    }
    int v = ++node_count;
    spl[v].val = val;
    spl[v].size = 1;
    connect(v, u, 1);
    splay(v, 0);
}

// 返回当前序列第 k 个元素所在节点，k 从 1 开始。
int kth(int k) {
    int u = root;
    while (u) {
        push_down(u);
        int left_size = get_size(spl[u].ch[0]);
        if (k <= left_size) u = spl[u].ch[0];
        else if (k == left_size + 1) return u;
        else {
            k -= left_size + 1;
            u = spl[u].ch[1];
        }
    }
    return 0;
}

void reverse_range(int l, int r) {
    // 序列两端额外放 0 与 n + 1 两个哨兵。
    // 所以第 l 个真实元素左边的边界是第 l 个节点。
    int left_boundary = kth(l);
    splay(left_boundary, 0);
    int right_boundary = kth(r + 2);
    splay(right_boundary, left_boundary);

    int middle = spl[right_boundary].ch[0];
    spl[middle].rev ^= 1;
}

void output(int u, bool &first) {
    if (!u) return;
    push_down(u);
    output(spl[u].ch[0], first);
    if (spl[u].val != 0 && spl[u].val != n + 1) {
        if (!first) cout << ' ';
        cout << spl[u].val;
        first = false;
    }
    output(spl[u].ch[1], first);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++) {
        append(i);
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
