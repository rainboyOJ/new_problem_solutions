/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 22:38
 * update_at: 2026-10-07 22:38
 */
// main.cpp：最小割（一本通 1761 / ROJ 1761）。
// 关键结论：割里恰好含 T 的一条边 e ⇔ 割的两侧就是 T-e 的两个连通块
// （T 是生成树，任一非平凡割至少跨过一条树边，跨过恰好一条就只能是 e），
// 于是该割大小 = 1 + cover[e]，cover[e] 是基本回路经过 e 的非树边条数。
// 答案 = 1 + min cover[e]，cover 用树上边差分（非树边给 u-v 路径 +1）统计。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20005;      // N <= 20000，留一点安全余量
const int MAXARC = 2 * MAXN; // 生成树邻接表：N-1 条树边 → 2(N-1) 条弧
const int LOG = 16;          // 2^15 = 32768 > 20000，16 层足够且留一层余量

int head[MAXN], nxt[MAXARC], to[MAXARC], arcCnt; // 生成树的链式前向星
int par[MAXN], dep[MAXN];                        // 以 1 为根：父亲与深度
int up[LOG][MAXN];                               // 倍增祖先，up[0][x] = par[x]
ll diffCnt[MAXN];                                // 树上边差分的累加数组
int order[MAXN];                                 // BFS 序，倒着扫就是自底向上

void addArc(int u, int v) {
    to[arcCnt] = v;
    nxt[arcCnt] = head[u];
    head[u] = arcCnt++;
}

// 快读：最大输入约 10^6 条边（2×10^6 个数），fread 缓冲比 scanf 稳
const int BUFSZ = 1 << 16;
char buf[BUFSZ];
int bufLen = 0, bufPos = 0;

int readChar() {
    if (bufPos == bufLen) {
        bufLen = fread(buf, 1, BUFSZ, stdin);
        bufPos = 0;
        if (bufLen <= 0) return -1; // EOF
    }
    return buf[bufPos++];
}

// 本题所有输入都是非负整数，读到 EOF 就返回已累积的值
int readInt() {
    int c = readChar();
    while (c >= 0 && (c < '0' || c > '9')) c = readChar(); // 跳过空白与换行
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return x;
}

// u、v 的最近公共祖先（倍增法，本题 N 小，倍增足够）
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int k = 0; k < LOG; k++)
        if (d >> k & 1) u = up[k][u];
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--)
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    return up[0][u];
}

int main() {
    ll T = readInt();
    if (T < 0) T = 0;
    while (T-- > 0) {
        ll n = readInt(), m = readInt();

        arcCnt = 0;
        for (int i = 1; i <= n; i++) {
            head[i] = -1;
            diffCnt[i] = 0;
        }

        for (int i = 0; i < n - 1; i++) { // 生成树 T 的 N-1 条边
            int u = readInt(), v = readInt();
            addArc(u, v);
            addArc(v, u);
        }

        if (n <= 1) { // 退化输入：T 没有树边，不存在"恰好含一条 T 边"的割（约束外）
            for (ll i = 0; i < m; i++) {
                readInt();
                readInt();
            }
            printf("0\n");
            continue;
        }

        // 迭代 BFS 建树（链状树也不会爆栈），同时把倍增祖先预处理出来
        int qh = 0, qt = 0;
        order[qt++] = 1;
        par[1] = 0;
        dep[1] = 0;
        for (int k = 0; k < LOG; k++) up[k][1] = 0;
        while (qh < qt) {
            int u = order[qh++];
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                if (v == par[u]) continue;
                par[v] = u;
                dep[v] = dep[u] + 1;
                up[0][v] = u;
                for (int k = 1; k < LOG; k++) up[k][v] = up[k - 1][up[k - 1][v]];
                order[qt++] = v;
            }
        }

        // 非树边：树上边差分，u-v 路径上所有树边 +1
        ll extra = m - n + 1; // 题面：M-N+1 条不在 T 中的边
        for (ll i = 0; i < extra; i++) {
            int u = readInt(), v = readInt();
            int w = lca(u, v);
            diffCnt[u]++;
            diffCnt[v]++;
            diffCnt[w] -= 2;
        }

        // 逆 BFS 序做子树和：节点 x 累加后的值就是树边 (par[x], x) 的覆盖数
        ll best = -1;
        for (int idx = n - 1; idx >= 1; idx--) {
            int x = order[idx];
            ll c = diffCnt[x];
            if (best < 0 || c < best) best = c;
            diffCnt[par[x]] += c;
        }

        printf("%lld\n", best + 1);
    }
    return 0;
}
