/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:10
 * update_at: 2026-10-05 03:17
 */
// 求两个不相交子数组异或和之和的最大值。
// 做法：枚举分割点 k，答案 = max(f(k) + g(k+1))；
// f(k) 是 A[1..k] 内最大子数组异或，g(i) 是 A[i..N] 内最大子数组异或。
// 子数组异或 = 两个前缀异或之异或，于是"以 i 结尾的最大子数组异或"
// 就是拿 P[i] 去 01-Trie 里和更早的所有前缀异或求最大异或（先查后插）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 400005;
const int MAXNODE = 24000100; // ch 槽位数上界：2*((N+1)*B+2)，B <= 30（每结点两个儿子槽）

int n;       // 数组元素个数
int bits;    // 值域二进制位数：异或结果不会超过 max(A) 的最高位
ll a[MAXN];  // 题目给出的数组，下标从 1 开始
ll b[MAXN];  // a 的反转数组，用来复用同一函数求后缀方向的 g
ll pre;      // 扫描过程中的当前前缀异或 P[i] = A[1] ^ ... ^ A[i]
ll f[MAXN];  // f[k]：A[1..k] 内所有子数组异或和的最大值
ll g[MAXN];  // g[k]：A[k..n] 内所有子数组异或和的最大值
ll ans;      // 最终答案

int ch[MAXNODE]; // ch[t*2+b]：01-Trie 中结点 t 的 b 儿子结点编号，0 表示不存在
int top_node;    // 已用结点的最大编号，1 号是根

// 向 Trie 插入一个前缀异或值 v
void trie_insert(ll v) {
    int t = 1;
    for (int s = bits - 1; s >= 0; --s) {
        int bit = (v >> s) & 1;
        int nxt = ch[t * 2 + bit];
        if (nxt == 0) { // 儿子不存在就新建结点
            ++top_node;
            ch[t * 2 + bit] = top_node;
            nxt = top_node;
        }
        t = nxt;
    }
}

// 在 Trie 已有的前缀异或值里找与 v 异或的最大值
// 贪心：高位收益 2^s 大于所有低位之和，反向儿子存在就走
ll trie_query(ll v) {
    int t = 1;
    ll acc = 0;
    for (int s = bits - 1; s >= 0; --s) {
        int bit = (v >> s) & 1;
        int w = ch[t * 2 + (bit ^ 1)]; // 最想要与当前位相反的儿子
        if (w != 0) {
            acc += 1LL << s;
            t = w;
        } else {
            t = ch[t * 2 + bit];
        }
    }
    return acc;
}

// 求 best[i] = x[1..i] 内所有子数组异或和的最大值，结果存入 best[1..m]
// 依次把前缀异或 P[0..m] 喂给 Trie：先查后插，保证 partner 下标更小、子数组非空
void calc_prefix_best(ll *x, int m, ll *best) {
    // 每次调用复用同一棵 Trie，只清空上次实际用到的结点区域：
    // 结点编号上界是 1 + (m+1)*bits，而 ch 槽位下标最大是结点号的 2 倍多
    memset(ch, 0, sizeof(int) * (2LL * ((m + 1) * bits + 2) + 2));
    top_node = 1;
    pre = 0;
    trie_insert(pre); // 先插入 P[0] = 0
    best[0] = 0;
    for (int i = 1; i <= m; ++i) {
        pre ^= x[i];
        ll h = trie_query(pre); // 以 i 结尾的最大子数组异或 = P[i] 与更早前缀的最大异或
        if (h > best[i - 1]) {
            best[i] = h;
        } else {
            best[i] = best[i - 1]; // 维护前缀最大值
        }
        trie_insert(pre);
    }
}

int main() {
    scanf("%d", &n);
    ll maxv = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        if (a[i] > maxv) maxv = a[i];
    }
    bits = 1;
    while ((1LL << bits) <= maxv) ++bits; // bit_length(max A)，至少为 1

    calc_prefix_best(a, n, f); // f[k]：前 k 个数里的最大子数组异或
    for (int i = 1; i <= n; ++i) b[i] = a[n + 1 - i]; // 反转数组
    calc_prefix_best(b, n, g); // 反转后 g[i] 存的是 b[1..i] 的答案
    for (int i = 1; i <= n / 2; ++i) { // 原地反转只扫前半，避免交换两遍写回原值
        ll t = g[i]; g[i] = g[n + 1 - i]; g[n + 1 - i] = t;
    } // 现在g[k] = A[k..n] 的答案

    ans = 0;
    for (int k = 1; k < n; ++k) { // 枚举分割点：左段在 A[1..k]，右段在 A[k+1..n]
        if (f[k] + g[k + 1] > ans) ans = f[k] + g[k + 1];
    }
    printf("%lld\n", ans);
    return 0;
}
