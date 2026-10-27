/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 15:48
 * update_at: 2026-10-27 15:48
 */
// U420425 线段树二分 2：区间加、区间和、单点赋值，以及区间内第一个让前缀和达到 d 的位置。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1000000 + 5;
const int MAXNODE = MAXN * 4;

int n, m;
ll a[MAXN];

// node[p].sum：结点 p 覆盖区间的元素和
// node[p].tag：结点 p 上待下传的加法标记（还没加到两个儿子上）
struct Node {
    ll sum;
    ll tag;
};
Node node[MAXNODE];

// 快速读入：本题最多 5e6 个整数，cin 在 1s 时限下不够用
const int BUFSIZE = 1 << 16;
char buf[BUFSIZE];
int buf_len = 0;
int buf_pos = 0;

inline char read_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFSIZE, stdin);
        buf_pos = 0;
        if (buf_len <= 0) return 0;
    }
    return buf[buf_pos++];
}

inline ll read_int() {
    char c = read_char();
    while (c != 0 && c != '-' && (c < '0' || c > '9')) c = read_char();
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = read_char();
    }
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = read_char();
    }
    return x * sign;
}

// 上推：父结点的区间和 = 两个儿子的区间和之和
void push_up(int p) {
    node[p].sum = node[p << 1].sum + node[p << 1 | 1].sum;
}

// 把结点 p 的整段区间（长度是 len）都加上 v
void apply_add(int p, int len, ll v) {
    node[p].sum += v * len;
    node[p].tag += v;
}

// 下推：把结点 p 的标记加到两个儿子上，并清空自己的标记
void push_down(int p, int l, int r) {
    if (node[p].tag == 0) return;
    int mid = (l + r) >> 1;
    apply_add(p << 1, mid - l + 1, node[p].tag);
    apply_add(p << 1 | 1, r - mid, node[p].tag);
    node[p].tag = 0;
}

void build(int p, int l, int r) {
    if (l == r) {
        node[p].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

// 区间加：把 [ql, qr] 内每个数加上 v
void range_add(int p, int l, int r, int ql, int qr, ll v) {
    if (ql <= l && r <= qr) {
        apply_add(p, r - l + 1, v);
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) range_add(p << 1, l, mid, ql, qr, v);
    if (qr > mid) range_add(p << 1 | 1, mid + 1, r, ql, qr, v);
    push_up(p);
}

// 区间和：[ql, qr] 内所有数之和
ll range_sum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return node[p].sum;
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    ll answer = 0;
    if (ql <= mid) answer += range_sum(p << 1, l, mid, ql, qr);
    if (qr > mid) answer += range_sum(p << 1 | 1, mid + 1, r, ql, qr);
    return answer;
}

// 单点赋值：把下标 pos 的数改成 v。先把沿路的标记推下去，叶子自己就是真实值
void point_assign(int p, int l, int r, int pos, ll v) {
    if (l == r) {
        node[p].sum = v;
        node[p].tag = 0;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (pos <= mid) point_assign(p << 1, l, mid, pos, v);
    else point_assign(p << 1 | 1, mid + 1, r, pos, v);
    push_up(p);
}

// 线段树二分：在 [ql, qr] 里找第一个使 a[ql] + ... + a[i] >= d 的下标 i，找不到返回 0。
// need = d - (a[ql] + ... + a[l-1]) 表示"还差多少"，扫过一整段就把它从 need 里扣掉，
// 于是每层只会往一条路走，单次询问 O(log n)。
// 调用前保证 [ql, qr] 与结点区间相交。
int find_first(int p, int l, int r, int ql, int qr, ll &need) {
    if (ql <= l && r <= qr) {
        if (node[p].sum < need) {  // 整段加起来都不够，整段跳过
            need -= node[p].sum;
            return 0;
        }
        if (l == r) return l;  // 叶子：加上 a[l] 后前缀和终于达到 d
        push_down(p, l, r);    // 要往下走，儿子的值必须先变成真实值
        int mid = (l + r) >> 1;
        int res = find_first(p << 1, l, mid, ql, qr, need);
        if (res != 0) return res;
        return find_first(p << 1 | 1, mid + 1, r, ql, qr, need);
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res = find_first(p << 1, l, mid, ql, qr, need);
    if (res == 0 && qr > mid) res = find_first(p << 1 | 1, mid + 1, r, ql, qr, need);
    return res;
}

int main() {
    n = (int)read_int();
    m = (int)read_int();
    for (int i = 1; i <= n; i++) a[i] = read_int();

    build(1, 1, n);

    for (int step = 1; step <= m; step++) {
        int op = (int)read_int();
        if (op == 1) {
            int x = (int)read_int();
            int y = (int)read_int();
            ll v = read_int();
            range_add(1, 1, n, x, y, v);
        } else if (op == 2) {
            int x = (int)read_int();
            int y = (int)read_int();
            printf("%lld\n", range_sum(1, 1, n, x, y));
        } else if (op == 3) {
            int x = (int)read_int();
            int y = (int)read_int();
            ll d = read_int();
            ll need = d;  // 还没累加过任何元素
            int answer = find_first(1, 1, n, x, y, need);
            if (answer == 0) answer = y + 1;  // [x, y] 里都到不了 d
            printf("%d\n", answer);
        } else {
            int x = (int)read_int();
            ll d = read_int();
            point_assign(1, 1, n, x, d);
        }
    }
    return 0;
}
