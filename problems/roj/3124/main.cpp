/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// Hotel：线段树维护连续空房，支持「最靠左的 d 间连续空房」与区间清空。
#include <cstdio>

typedef long long ll;

const ll MAXN = 100005;
const ll NONE = -1;  // 延迟标记：-1 无标记，0 整段清空，1 整段入住
const ll OCCUPY = 1, CLEAR = 0;

ll length[MAXN * 4]; // 每个节点覆盖的房间数
ll pre[MAXN * 4];    // 该段从左端起的最长连续空房数
ll suf[MAXN * 4];    // 该段从右端起的最长连续空房数
ll best[MAXN * 4];   // 该段内部的最长连续空房数
ll lazy[MAXN * 4];   // 延迟标记

// 建树：叶子记区间长度（超出 n 的补 0），初始全部空房
ll prepare(ll n) {
    ll M = 1; // 叶子数，同时就是房间坐标的上界
    while (M < n) M <<= 1;
    ll size = M << 1;
    for (ll i = 0; i < size; i++) {
        length[i] = 0;
        pre[i] = suf[i] = best[i] = 0;
        lazy[i] = NONE;
    }
    for (ll i = M; i < size; i++) {
        if (1 <= i - M + 1 && i - M + 1 <= n) length[i] = 1;
        // 叶子：三个统计量都与区间长度相同（length 只取 0 / 1）
        pre[i] = suf[i] = best[i] = length[i];
    }
    for (ll i = M - 1; i >= 1; i--) { // 自底向上累加出每个节点的区间长度
        length[i] = length[i << 1] + length[i << 1 | 1];
        pre[i] = suf[i] = best[i] = length[i];
    }
    return M;
}

// 把 node 整段刷成 color：入住则空房归零，清空则整段都是空房
void apply(ll node, ll color) {
    ll empty = (color == OCCUPY) ? 0 : length[node];
    pre[node] = suf[node] = best[node] = empty;
    lazy[node] = color;
}

// 把 node 的延迟标记下传给孩子，并清掉自己的标记
void push(ll node) {
    ll tag = lazy[node];
    if (tag != NONE) {
        apply(node << 1, tag);
        apply(node << 1 | 1, tag);
        lazy[node] = NONE;
    }
}

// 由两个孩子重算 node 的三个空房统计量
void pull(ll node) {
    ll left = node << 1, right = node << 1 | 1;
    pre[node] = pre[left] + (pre[left] == length[left] ? pre[right] : 0);
    suf[node] = suf[right] + (suf[right] == length[right] ? suf[left] : 0);
    ll b = best[left] > best[right] ? best[left] : best[right];
    ll cross = suf[left] + pre[right];
    best[node] = b > cross ? b : cross;
}

// 把房间区间 [ql, qr] 整段刷成 color
void modify(ll node, ll l, ll r, ll ql, ll qr, ll color) {
    if (ql <= l && r <= qr) { // 当前段被完全覆盖，整段打标记
        apply(node, color);
        return;
    }
    push(node);
    ll mid = (l + r) >> 1;
    if (ql <= mid) modify(node << 1, l, mid, ql, qr, color);
    if (qr > mid) modify(node << 1 | 1, mid + 1, r, ql, qr, color);
    pull(node);
}

// 找最靠左的、能装下 d 个连续空房的起点房间号；装不下返回 0
ll query(ll node, ll l, ll r, ll d) {
    if (best[node] < d) return 0;
    if (l == r) return l; // 走到叶子说明 d 必为 1
    push(node);
    ll mid = (l + r) >> 1;
    ll left = node << 1, right = node << 1 | 1;
    if (best[left] >= d) return query(left, l, mid, d);      // 优先最左
    if (suf[left] + pre[right] >= d) return mid - suf[left] + 1; // 跨在交界处
    return query(right, mid + 1, r, d);
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    ll M = prepare(n);

    ll outs = 0; // 真正输出过的询问个数
    for (ll q = 0; q < m; q++) {
        ll op;
        scanf("%lld", &op);
        if (op == 1) {
            ll d;
            scanf("%lld", &d);
            ll start = query(1, 1, M, d);
            printf("%lld\n", start);
            outs++;
            if (start) { // 找到才真的入住
                modify(1, 1, M, start, start + d - 1, OCCUPY);
            }
        } else {
            ll x, d;
            scanf("%lld %lld", &x, &d);
            modify(1, 1, M, x, x + d - 1, CLEAR);
        }
    }
    if (outs == 0) printf("\n"); // 与 Python 的 print('\n'.join([])) 一致
    return 0;
}
