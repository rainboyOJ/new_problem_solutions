/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 20:18
 * update_at: 2026-10-29 20:18
 */
// main.cpp：ROJ 1820 区间最大利润（线段树）
// 询问 max(A[j] - A[i])，l <= i < j <= r。对每个区间只需要记住三件事：
//   minv：区间内最低价（最适合买入）
//   maxv：区间内最高价（最适合卖出）
//   best：区间内 max(A[j] - A[i])，i < j
// 合并左右两段 L、R 时，最优交易要么全在 L 里、要么全在 R 里、
// 要么在 L 里买在 R 里卖，第三种的利润是 R.maxv - L.minv。
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

const ll NEG_INF = -2000000000000000000LL; // 答案可能为负，初值取得足够小

// 一段区间的交易信息
struct Node {
    ll minv; // 区间内最低价
    ll maxv; // 区间内最高价
    ll best; // 区间内 max(A[j] - A[i])，要求买入时刻早于卖出时刻
};

ll n, q;
ll a[MAXN];        // a[i]：第 i 天的价格，下标从 1 开始
Node tree[MAXN * 4]; // tree[p]：结点 p 覆盖的那段区间的交易信息

// p 的左儿子与右儿子编号（模板约定的 1 下标完全二叉树编号）
ll ls(ll p) { return p << 1; }
ll rs(ll p) { return p << 1 | 1; }

// 把左右相邻的两段合并成一段
Node merge_node(Node left_seg, Node right_seg) {
    Node res;
    res.minv = min(left_seg.minv, right_seg.minv);
    res.maxv = max(left_seg.maxv, right_seg.maxv);
    // 三种来源：全在左段、全在右段、左段买入右段卖出
    res.best = max(max(left_seg.best, right_seg.best), right_seg.maxv - left_seg.minv);
    return res;
}

// 建树：叶子就是一天的价格
void build(ll p, ll l, ll r) {
    if (l == r) {
        tree[p].minv = a[l];
        tree[p].maxv = a[l];
        tree[p].best = NEG_INF; // 只有一天，构不成先买后卖
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    tree[p] = merge_node(tree[ls(p)], tree[rs(p)]);
}

// 查询区间 [ql, qr] 的交易信息
Node query(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) return tree[p]; // 当前结点被完全覆盖

    ll mid = (l + r) >> 1;
    if (qr <= mid) return query(ls(p), l, mid, ql, qr);       // 只查左儿子
    if (ql > mid) return query(rs(p), mid + 1, r, ql, qr);    // 只查右儿子

    // 跨过中点：左右都要查，再按顺序合并（左段在前，右段在后）
    Node left_seg = query(ls(p), l, mid, ql, qr);
    Node right_seg = query(rs(p), mid + 1, r, ql, qr);
    return merge_node(left_seg, right_seg);
}

void solve() {
    scanf("%lld %lld", &n, &q);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    build(1, 1, n);

    for (ll i = 0; i < q; i++) {
        ll l, r;
        scanf("%lld %lld", &l, &r);
        Node res = query(1, 1, n, l, r);
        printf("%lld\n", res.best);
    }
}

int main() {
    solve();
    return 0;
}
