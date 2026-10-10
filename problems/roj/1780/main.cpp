/**
 * 1780 修墙
 *
 * 题意：有一个无限大的黑白矩阵，由 "AA / AB"（B 全黑）反复迭代生成。
 *       若把行列都从 0 开始编号，可以证明格子 (i, j) 是白色当且仅当 i & j == 0。
 *       白格视为用户，四连通的白格互相可达，每次询问一个矩形，输出矩形内白格的连通块数。
 *
 * 性质：所有白格（连同四邻边）构成一棵以 (0,0) 为根的树。
 *   lsb(i) 表示 i 的最低位 1 的位置，规定 lsb(0) = +inf。
 *   对白格 (i, j)（i & j == 0，故 i、j 不可能有相同的 lsb，除非都为 0）：
 *     lsb(i) < lsb(j) 时，(i-1, j) 是白格，它是 (i, j) 唯一的“向标号更小方向”的邻居；
 *     lsb(j) < lsb(i) 时，(i, j-1) 是白格，同理。
 *   把前一种情况的 (i-1, j)、后一种情况的 (i, j-1) 定为 (i, j) 的父亲（(0,0) 无父亲，为树根）。
 *   于是白格图是树，任意矩形诱导出的子图是森林。
 *
 * 计数方式：森林中每个连通块恰有一个“顶端”点（把树根祖先方向视为块外），
 *   所以矩形 R 内的连通块数 = #{白格 v ∈ R : v 的父亲不在 R 中}（树根 (0,0) 只要落在 R 内就算一个）。
 *   设矩形为 [x1, x2] × [y1, y2]（0 下标）：
 *     A：父亲 (i-1, j) 出界 <=> i == x1 且 lsb(x1) < lsb(j)：
 *        A = #{ j ∈ [y1, y2] : j & Mx == 0 }，Mx = x1 | (2^lsb(x1) - 1)（x1 > 0 时；否则 A = 0）
 *     B：父亲 (i, j-1) 出界 <=> j == y1 且 lsb(y1) < lsb(i)：
 *        B = #{ i ∈ [x1, x2] : i & My == 0 }，My = y1 | (2^lsb(y1) - 1)（y1 > 0 时；否则 B = 0）
 *     若 (x1, y1) == (0, 0) 还要再加 1（全局树根本身）。
 *   其中 #{ j ∈ [0, X] : j & M == 0 } 用数位计数：从高位到低位扫，
 *   遇到 X 的位为 1 时，让 j 该位取 0、低位在 M 为 0 的位上自由取，贡献 2^(自由位数)；
 *   但若该位 M 也为 1，则 j 无法继续与 X 前缀相同，直接结束；否则继续（j 该位取 1）。
 *   扫完再补上 j == X 本身。单次 O(log C)，每组询问 4 次，$q = 10^6$ 时完全够用。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int TOPBIT = 30;      // 坐标 < 2^30
ll pw2[TOPBIT + 2];         // 2 的幂

/* ---------- 快速读入 ---------- */
static char inbuf[1 << 20];
static int inlen = 0, inpos = 0;

inline int nextChar() {
    if (inpos == inlen) {
        inlen = (int)fread(inbuf, 1, sizeof(inbuf), stdin);
        inpos = 0;
        if (inlen <= 0) return -1;
    }
    return inbuf[inpos++];
}

inline ll readInt() {
    int c = nextChar();
    while (c != -1 && (c < '0' || c > '9')) c = nextChar();
    ll v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + (c - '0'); c = nextChar(); }
    return v;
}

/* ---------- 快速输出 ---------- */
static char outbuf[1 << 21];
static int outlen = 0;

inline void flushOut() {
    if (outlen) { fwrite(outbuf, 1, outlen, stdout); outlen = 0; }
}

inline void putChar(char c) {
    if (outlen == (int)sizeof(outbuf)) flushOut();
    outbuf[outlen++] = c;
}

inline void writeInt(ll v) {
    if (v == 0) { putChar('0'); putChar('\n'); return; }
    char tmp[24];
    int n = 0;
    while (v > 0) { tmp[n++] = (char)('0' + (int)(v % 10)); v /= 10; }
    while (n > 0) putChar(tmp[--n]);
    putChar('\n');
}

/* ---------- 数位计数 ---------- */
// 求 #{ j : 0 <= j <= X, j & M == 0 }；X < 0 时返回 0
ll countNoBit(ll X, ll M) {
    if (X < 0) return 0;
    ll res = 0;
    for (int b = TOPBIT; b >= 0; b--) {
        if ((X >> b) & 1LL) {
            // j 的第 b 位取 0（严格小于 X），低位只能取 M 为 0 的位
            int freeBits = b - __builtin_popcountll(M & (pw2[b] - 1));
            res += pw2[freeBits];
            if ((M >> b) & 1LL) return res;     // 该位 M == 1，j 无法继续等于 X 的前缀
        }
        // X 该位为 0：j 该位也只能取 0，与 X 相同，继续
    }
    if ((X & M) == 0) res++;                    // j == X 本身
    return res;
}

int main() {
    pw2[0] = 1;
    for (int i = 1; i <= TOPBIT + 1; i++) pw2[i] = pw2[i - 1] << 1;

    ll q = readInt();
    for (ll qi = 0; qi < q; qi++) {
        ll x1 = readInt() - 1, y1 = readInt() - 1;
        ll x2 = readInt() - 1, y2 = readInt() - 1;
        ll ans = 0;
        if (x1 > 0) {
            // 第 x1 行上父亲越过上边界的白格
            int p = __builtin_ctzll(x1);
            ll M = x1 | (pw2[p] - 1);
            ans += countNoBit(y2, M) - countNoBit(y1 - 1, M);
        }
        if (y1 > 0) {
            // 第 y1 列上父亲越过左边界的白格
            int p = __builtin_ctzll(y1);
            ll M = y1 | (pw2[p] - 1);
            ans += countNoBit(x2, M) - countNoBit(x1 - 1, M);
        }
        if (x1 == 0 && y1 == 0) ans++;          // 全局树根 (0,0)
        writeInt(ans);
    }
    flushOut();
    return 0;
}
