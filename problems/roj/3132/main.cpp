/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 区间最大异或和：可持久化 01 Trie + 分块预处理（块内右端固定、左端固定的最优值）。
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long ll;

const ll MAX_BIT = 30; // Ai < 2^31
const ll MAXNODE = 500000;

ll CNT[MAXNODE]; // 子树计数
ll CH0[MAXNODE];
ll CH1[MAXNODE];
std::vector<ll> RO; // RO[k] = 插入 S[0..k-1] 之后的根

ll node_cnt = 1; // 0 号是空版本

// 把前缀异或 x 插入 Trie，沿路复制出一个新版本并返回新版本的根
ll trie_extend(ll prev, ll x) {
    ll root = node_cnt++;
    CNT[root] = CNT[prev] + 1;
    CH0[root] = CH0[prev]; // 没走到的另一支原样共享
    CH1[root] = CH1[prev];
    ll cur = root, old = prev;
    for (ll k = MAX_BIT; k >= 0; k--) {
        ll bit = (x >> k) & 1;
        ll old_child = bit ? CH1[old] : CH0[old];
        ll nx = node_cnt++;
        CNT[nx] = CNT[old_child] + 1;
        CH0[nx] = CH0[old_child];
        CH1[nx] = CH1[old_child];
        if (bit == 0) CH0[cur] = nx;
        else CH1[cur] = nx;
        cur = nx;
        old = old_child;
    }
    return root;
}

// 前缀异或区间 S[lo..hi] 中，与 x 异或的最大值
ll range_max_xor(ll hi, ll lo, ll x) {
    ll u = RO[hi + 1], v = RO[lo]; // v 是 lo 之前的版本，作差得到区间
    ll best = 0;
    for (ll k = MAX_BIT; k >= 0; k--) {
        ll bit = (x >> k) & 1;
        if (bit) { // 想让结果这一位为 1 就走反方向 0
            ll pu = CH0[u], pv = CH0[v];
            if (CNT[pu] > CNT[pv]) {
                best |= 1LL << k;
                u = pu; v = pv;
            } else {
                u = CH1[u]; v = CH1[v];
            }
        } else { // 想走反方向 1
            ll pu = CH1[u], pv = CH1[v];
            if (CNT[pu] > CNT[pv]) {
                best |= 1LL << k;
                u = pu; v = pv;
            } else {
                u = CH0[u]; v = CH0[v];
            }
        }
    }
    return best;
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    std::vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    // 前缀异或 S[i] = A1 xor ... xor Ai，子段异或和 = S[i-1] xor S[j]
    std::vector<ll> s(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        s[i] = s[i - 1] ^ a[i - 1];
    }

    RO.assign(n + 2, 0); // RO[0] 是空版本，RO[k+1] = 插入 S[0..k] 之后的根
    for (ll k = 0; k <= n; k++) {
        RO[k + 1] = trie_extend(RO[k], s[k]);
    }

    ll block = (ll)std::sqrt((double)n); // 块长 ~sqrt(N)
    if (block < 1) block = 1;
    ll block_count = (n + block - 1) / block;

    std::vector<ll> g(n + 1, 0); // g[i]：从 i 到所在块末尾的最大子段异或和
    for (ll start = 0; start < n; start += block) {
        ll block_lo = start + 1;
        ll block_hi = start + block;
        if (block_hi > n) block_hi = n;
        ll best = 0;
        for (ll i = block_hi; i >= block_lo; i--) {
            ll cand = range_max_xor(block_hi, i, s[i - 1]);
            if (cand > best) best = cand;
            g[i] = best;
        }
    }

    // f[bi][j - base]：起点 >= bi*block+1 且终点 <= j 的最大子段异或和
    std::vector<std::vector<ll> > f(block_count + 1);
    for (ll bi = 1; bi < block_count; bi++) {
        ll base = bi * block + 1;
        f[bi].assign(n + 2, 0);
        ll best = 0;
        for (ll j = base; j <= n; j++) {
            ll cand = range_max_xor(j - 1, base - 1, s[j]);
            if (cand > best) best = cand;
            f[bi][j] = best;
        }
    }

    ll last = 0; // 在线询问：上一问的答案参与下一问的解码
    for (ll q = 0; q < m; q++) {
        ll x, y;
        scanf("%lld %lld", &x, &y);
        ll p = (x + last) % n + 1, qq = (y + last) % n + 1;
        ll l = p, r = qq;
        if (l > r) {
            ll t = l; l = r; r = t;
        }
        ll left_block = (l - 1) / block, right_block = (r - 1) / block;
        ll best;
        if (left_block == right_block) { // 同块：右端点最多扫一个块
            best = 0;
            for (ll j = l; j <= r; j++) {
                ll cand = range_max_xor(j - 1, l - 1, s[j]);
                if (cand > best) best = cand;
            }
        } else {
            ll left_end = (left_block + 1) * block; // 左段末尾，一定 < r
            // 三段覆盖 [l, r] 内所有子段：左段内 / 跨过左段 / 从第一个完整块起
            ll across = 0;
            for (ll t = l - 1; t < left_end; t++) {
                ll cand = range_max_xor(r, left_end + 1, s[t]);
                if (cand > across) across = cand;
            }
            best = g[l];
            if (across > best) best = across;
            ll third = f[left_block + 1][r];
            if (third > best) best = third;
        }
        last = best;
        printf("%lld\n", last);
    }
    return 0;
}
