/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:34
 * update_at: 2026-10-07 20:34
 */

// 1741《电子速度》
// 题意：n 个电子，第 i 个的速度 v_i = (x_i, y_i)。
//   操作 1 p x y：把 v_p 改成 (x, y)；
//   操作 2 l r ：询问 Σ_{l≤i<j≤r} |v_i × v_j|² mod 20170927。
//
// 关键恒等式（叉积平方对求和可以完全展开）：
//   Σ_{i<j} (x_i·y_j − x_j·y_i)²
//     = (Σ x²)·(Σ y²) − (Σ x·y)²
// 证明：左边 = Σ_{i<j} x_i²y_j² + Σ_{i<j} x_j²y_i² − 2Σ_{i<j} x_ix_jy_iy_j
//            = Σ_{i≠j} x_i²y_j² − 2Σ_{i<j} (x_iy_i)(x_jy_j)
//            = [ (Σx²)(Σy²) − Σx_i²y_i² ] − [ (Σxy)² − Σx_i²y_i² ]
//            = (Σx²)(Σy²) − (Σxy)²
// 所以区间询问只要拿到三个区间和：Σx²、Σy²、Σx·y。
// 单点修改 → 三个量都只有一处变化 → 树状数组维护三个分量即可。
//
// 数据结构：一棵树状数组，每个结点同时存三个分量（Σx²、Σy²、Σx·y）。
// 时间 O((n + m) log n)，空间 O(n)（n = 10^6 时约 24 MB）。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 20170927;
const int MAXN = 1000000 + 5;

int n, m;

struct Node {
    ll px; // Σ x²
    ll py; // Σ y²
    ll pr; // Σ x·y
};

struct Vec {
    int x;
    int y;
};

Node tree[MAXN]; // 树状数组：下标 i 管辖一段区间，三个分量都恒保存在 [0, MOD)
Vec vel[MAXN];   // 每个电子当前的速度

// ── 快速输入：fread 缓冲，处理 n, m ≤ 10^6 的量级 ──
static char inbuf[1 << 20];
static int inpos = 0, inlen = 0;

inline int readChar() {
    if (inpos == inlen) {
        inlen = fread(inbuf, 1, sizeof(inbuf), stdin);
        inpos = 0;
        if (inlen <= 0) return -1;
    }
    return (unsigned char)inbuf[inpos++];
}

inline int readInt() {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9')) c = readChar();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return x;
}

// ── 快速输出：攒满一个缓冲区再整体写出 ──
static char outbuf[1 << 20];
static int outpos = 0;

inline void flushOut() {
    if (outpos > 0) {
        fwrite(outbuf, 1, outpos, stdout);
        outpos = 0;
    }
}

inline void writeInt(ll v) {
    char tmp[24];
    int k = 0;
    if (v == 0) tmp[k++] = '0';
    while (v > 0) {
        tmp[k++] = '0' + v % 10;
        v /= 10;
    }
    if (outpos + k + 1 > (int)sizeof(outbuf)) flushOut();
    while (k > 0) outbuf[outpos++] = tmp[--k];
    outbuf[outpos++] = '\n';
}

// 在下标 pos 处把三个分量各加上 d*（增量已归一到 [0, MOD)）
void add(int pos, ll dx, ll dy, ll dr) {
    for (int i = pos; i <= n; i += i & -i) {
        tree[i].px += dx;
        if (tree[i].px >= MOD) tree[i].px -= MOD;
        tree[i].py += dy;
        if (tree[i].py >= MOD) tree[i].py -= MOD;
        tree[i].pr += dr;
        if (tree[i].pr >= MOD) tree[i].pr -= MOD;
    }
}

// 前 pos 个电子三个分量之和（各自对 MOD 取模）
Node prefixSum(int pos) {
    Node s;
    s.px = s.py = s.pr = 0;
    for (int i = pos; i > 0; i -= i & -i) {
        s.px += tree[i].px;
        s.py += tree[i].py;
        s.pr += tree[i].pr;
    }
    s.px %= MOD;
    s.py %= MOD;
    s.pr %= MOD;
    return s;
}

int main() {
    n = readInt();
    m = readInt();

    for (int i = 1; i <= n; i++) {
        int x = readInt() % MOD;
        int y = readInt() % MOD;
        vel[i].x = x;
        vel[i].y = y;
        add(i, (ll)x * x % MOD, (ll)y * y % MOD, (ll)x * y % MOD);
    }

    for (int q = 1; q <= m; q++) {
        int op = readInt();
        if (op == 1) {
            int p = readInt();
            int x = readInt() % MOD;
            int y = readInt() % MOD;
            int ox = vel[p].x, oy = vel[p].y;

            ll dx = ((ll)x * x - (ll)ox * ox) % MOD;
            if (dx < 0) dx += MOD;
            ll dy = ((ll)y * y - (ll)oy * oy) % MOD;
            if (dy < 0) dy += MOD;
            ll dr = ((ll)x * y - (ll)ox * oy) % MOD;
            if (dr < 0) dr += MOD;
            add(p, dx, dy, dr);

            vel[p].x = x;
            vel[p].y = y;
        } else {
            int l = readInt(), r = readInt();
            Node sr = prefixSum(r);
            Node sl = prefixSum(l - 1);
            ll px = (sr.px - sl.px + MOD) % MOD; // 区间内的 Σ x²
            ll py = (sr.py - sl.py + MOD) % MOD; // 区间内的 Σ y²
            ll pr = (sr.pr - sl.pr + MOD) % MOD; // 区间内的 Σ x·y

            ll ans = (px * py - pr * pr) % MOD;
            if (ans < 0) ans += MOD;
            writeInt(ans);
        }
    }

    flushOut();
    return 0;
}
