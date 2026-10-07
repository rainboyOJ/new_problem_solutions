/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:19
 * update_at: 2026-10-08 06:19
 *
 * ROJ 1815 「放石子」：SG 定理 + 二进制线性基（逆拓扑序）
 *
 * 石子之间互不影响（一步只动一颗），把 q 颗石子看成 q 个独立子游戏，
 * 答案 = 各石子所在点 SG 值的异或和，非 0 先手胜。
 *
 * 单点 SG：设颜色 c 的所有出边终点 SG 的异或和为 h_c。若一次操作选颜色集合 S，
 * 到达局面的 SG 值恰为 XOR_{c in S} h_c，于是 x 的可达 SG 值集合 = span{h_c}
 * （F_2 上的线性子空间），故 SG(x) = mex(span{h_c})。
 *
 * 用「最高位为主元」的线性基：位置 0..j-1 全为主元 <=> [0, 2^j) 全在 span 内；
 * 而位置 j 非主元 <=> 2^j 不在 span 内。所以 mex(span) = 2^(最小的非主元位)。
 *
 * 位宽：SG 值恒为 2 的幂。若某点 SG = 2^k，则它的后继里必须出现指数 0..k-1 的点，
 * 指数为 i 的后继自己至少要有 i 条出边，再加上 x 自己的 k 条出边，得
 *   m >= k + k(k-1)/2 = k(k+1)/2，
 * m <= 5000 时 k <= 99，故 256 位（bitset）有充足余量。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 205;   // 点数上限 200
const int MAXM = 5005;  // 边数上限 5000
const int W = 256;      // SG 值的位宽（指数上界 99，此处留足余量）

typedef bitset<W> BS;

struct Edge {   // 一条有向边
    int from, to, col;
};
struct Range {  // 节点 x 的出边在 es 中占据的下标区间 [l, r)
    int l, r;
};
struct Redge {  // 反图上的边：由 to 指回它的前驱 from，用于逆拓扑递减剩余出度
    int from, nxt;
};

Edge es[MAXM];
Range rg[MAXN];
Redge re[MAXM];
int rhead[MAXN], rcnt;
int rest[MAXN];   // 逆拓扑 Kahn 的剩余出度计数
BS sg[MAXN];      // sg[x]：单颗石子放在 x 上时的 SG 值（只有一位为 1，或全 0）
BS basis[W];      // 线性基：basis[b] 的主元（最高位）是 b
char isPivot[W];
int que[MAXN];

bool cmpEdge(const Edge &a, const Edge &b) {  // 按 (起点, 颜色) 排序，让同色出边聚成一段
    if (a.from != b.from) return a.from < b.from;
    return a.col < b.col;
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0;
    for (int i = 0; i < m; i++) {
        int s, t, c;
        scanf("%d %d %d", &s, &t, &c);
        es[i].from = s;
        es[i].to = t;
        es[i].col = c;
        re[++rcnt].from = s;              // 反图：t 的前驱是 s
        re[rcnt].nxt = rhead[t];
        rhead[t] = rcnt;
    }
    sort(es, es + m, cmpEdge);
    for (int i = 0, p = 0; i <= n; i++) {  // 切出每个点的出边区间
        rg[i].l = p;
        while (p < m && es[p].from == i) p++;
        rg[i].r = p;
    }

    int qh = 0, qt = 0;
    for (int i = 1; i <= n; i++) {
        rest[i] = rg[i].r - rg[i].l;                // 原图出度
        if (rest[i] == 0) que[qt++] = i;            // 出度为 0：无路可走，SG = 0
    }
    while (qh < qt) {
        int x = que[qh++];
        if (rg[x].r > rg[x].l) {                    // 有出边的点才需要求 SG
            for (int b = 0; b < W; b++) isPivot[b] = 0;
            for (int i = rg[x].l; i < rg[x].r;) {
                int c = es[i].col;
                BS h;                               // 颜色 c 下所有出边终点 SG 的异或和
                while (i < rg[x].r && es[i].col == c) {
                    h ^= sg[es[i].to];
                    i++;
                }
                for (int b = W - 1; b >= 0; b--) {  // 把 h 插入线性基
                    if (!h[b]) continue;
                    if (!isPivot[b]) {
                        isPivot[b] = 1;
                        basis[b] = h;
                        break;
                    }
                    h ^= basis[b];
                }
            }
            for (int b = 0; b < W; b++)             // mex(span) = 2^(最小的非主元位)
                if (!isPivot[b]) {
                    sg[x].set(b);
                    break;
                }
        }
        for (int i = rhead[x]; i; i = re[i].nxt) {  // x 的 SG 已定，回报给所有前驱
            int y = re[i].from;
            if (--rest[y] == 0) que[qt++] = y;
        }
    }

    ll qn;
    if (scanf("%lld", &qn) != 1) return 0;
    BS total;
    for (int i = 0; i < qn; i++) {
        int a;
        scanf("%d", &a);
        total ^= sg[a];                             // 局面 SG = 各颗石子 SG 的异或和
    }
    printf("%d\n", total.any() ? 1 : 0);
    return 0;
}
