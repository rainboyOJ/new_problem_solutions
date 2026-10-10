/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:55
 * update_at: 2026-10-08 06:55
 */
// 一本通 1993 开关switch：区间取反 + 区间求和，带懒标记的线段树
// 核心性质：长度为 len 的区间里有 sum 盏灯亮着，整段取反后亮灯数就是 len - sum，
// 所以每个节点只需要维护 len 与 sum，取反操作可以整段 O(1) 完成。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100000 + 5;

ll n, m;  // 灯的数目、操作的数目

struct Node {
    ll sum;    // 本段区间内开着的灯数
    ll len;    // 本段区间的长度，用于整段取反：sum -> len - sum
    char tag;  // 懒标记：1 表示本段整体还需要取反一次，0 表示不需要（取反两次互相抵消）
};
Node node[MAXN * 4];  // 线段树节点，u 的两个儿子是 u<<1 与 u<<1|1

// 建树：灯初始全关，所以所有节点的 sum 都是 0，只需把长度与标记填好
void build(int u, ll l, ll r) {
    node[u].sum = 0;
    node[u].len = r - l + 1;
    node[u].tag = 0;
    if (l == r) return;
    ll mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

// 把 u 的懒标记下传给两个儿子：它们各自按"自己的长度"取反，标记异或累加
void push_down(int u) {
    if (node[u].tag == 0) return;
    int left = u << 1, right = u << 1 | 1;
    node[left].sum = node[left].len - node[left].sum;      // 左儿子按自己的长度取反
    node[right].sum = node[right].len - node[right].sum;   // 右儿子按自己的长度取反
    node[left].tag ^= 1;
    node[right].tag ^= 1;
    node[u].tag = 0;
}

// 区间取反：把 [ql, qr] 内每盏灯的状态反转
void update(int u, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) {
        node[u].sum = node[u].len - node[u].sum;  // 整段被覆盖：亮灯数变成 len - sum
        node[u].tag ^= 1;
        return;
    }
    push_down(u);  // 要往儿子走了，标记必须先落地
    ll mid = (l + r) >> 1;
    if (ql <= mid) update(u << 1, l, mid, ql, qr);
    if (qr > mid) update(u << 1 | 1, mid + 1, r, ql, qr);
    node[u].sum = node[u << 1].sum + node[u << 1 | 1].sum;  // 回溯时用儿子的新值更新自己
}

// 区间查询：返回 [ql, qr] 内开着的灯数
ll query(int u, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) return node[u].sum;
    push_down(u);
    ll mid = (l + r) >> 1, res = 0;
    if (ql <= mid) res += query(u << 1, l, mid, ql, qr);
    if (qr > mid) res += query(u << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

int main() {
    scanf("%lld %lld", &n, &m);
    build(1, 1, n);
    for (ll i = 1; i <= m; i++) {
        ll c, a, b;
        scanf("%lld %lld %lld", &c, &a, &b);
        if (c == 0)
            update(1, 1, n, a, b);  // 第一种操作：区间取反
        else
            printf("%lld\n", query(1, 1, n, a, b));  // 第二种操作：输出该区间亮灯数
    }
    return 0;
}
