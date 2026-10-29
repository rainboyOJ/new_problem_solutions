/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 20:22
 * update_at: 2026-10-29 20:22
 */
// main2.cpp：ROJ 1820 区间最大利润（倍增）
// 预处理 jump[k][i] = 区间 [i, i + 2^k - 1] 的交易信息，由 k-1 层的相邻两段合并得到。
// 查询 [l, r] 时从大到小枚举 2^k，能放下就取走这一段并让 l 前移，直到区间被取完。
//
// 注意：这里不能写成常见的「重叠 ST 表」查询。那种写法取两块长度为 2^k 的区间让它们
// 重叠，正确性依赖合并运算幂等（op(x, x) = x）。本题的 best 含跨段项 R.maxv - L.minv，
// 两块重叠时会把同一段既当左半又当右半，配出「先卖后买」的非法对，答案会偏大。
// 下面的写法每段只合并一次、互不重叠，所以不依赖幂等性。
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXLOG = 18; // 2^17 = 131072 > 10^5，够用

const ll NEG_INF = -2000000000000000000LL; // 答案可能为负，初值取得足够小

// 一段区间的交易信息，含义与 main.cpp 完全一致
struct Node {
    ll minv; // 区间内最低价
    ll maxv; // 区间内最高价
    ll best; // 区间内 max(A[j] - A[i])，要求买入时刻早于卖出时刻
};

ll n, q;
ll a[MAXN];              // a[i]：第 i 天的价格，下标从 1 开始
Node jump_table[MAXLOG][MAXN]; // jump_table[k][i]：区间 [i, i + 2^k - 1] 的交易信息
int max_log;             // 满足 2^max_log <= n 的最大 max_log

// 把左右相邻的两段合并成一段
Node merge_node(Node left_seg, Node right_seg) {
    Node res;
    res.minv = min(left_seg.minv, right_seg.minv);
    res.maxv = max(left_seg.maxv, right_seg.maxv);
    res.best = max(max(left_seg.best, right_seg.best), right_seg.maxv - left_seg.minv);
    return res;
}

// 预处理：第 0 层是每个单点，之后每层由上一层相邻两段合并
void build_table() {
    for (ll i = 1; i <= n; i++) {
        jump_table[0][i].minv = a[i];
        jump_table[0][i].maxv = a[i];
        jump_table[0][i].best = NEG_INF; // 只有一天，构不成先买后卖
    }

    max_log = 0;
    while ((1 << (max_log + 1)) <= n) max_log++;

    for (int k = 1; k <= max_log; k++) {
        int half = 1 << (k - 1); // 半段长度 2^(k-1)
        for (ll i = 1; i + (1 << k) - 1 <= n; i++) {
            jump_table[k][i] = merge_node(jump_table[k - 1][i],
                                          jump_table[k - 1][i + half]);
        }
    }
}

// 查询 [l, r]：从大到小尝试 2^k，放得下就取走这一段，等价于倍增文章里「能跳就跳」
Node query(ll l, ll r) {
    Node res;
    bool has_piece = false; // 是否已经取到第一段

    for (int k = max_log; k >= 0; k--) {
        if (l + (1 << k) - 1 > r) continue; // 这一段放不进剩余区间，跳过
        if (!has_piece) {
            res = jump_table[k][l];
            has_piece = true;
        } else {
            res = merge_node(res, jump_table[k][l]);
        }
        l += 1 << k; // 这一段已经取走，左端点前移
    }
    return res;
}

void solve() {
    scanf("%lld %lld", &n, &q);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    build_table();

    for (ll i = 0; i < q; i++) {
        ll l, r;
        scanf("%lld %lld", &l, &r);
        Node res = query(l, r);
        printf("%lld\n", res.best);
    }
}

int main() {
    solve();
    return 0;
}
