// 一本通 1746《矩阵最值》 —— 二维稀疏表（ST 表）
//
// 题意：给定 n 行 m 列的矩阵，K 次询问，每次问以 (x1,y1) 为左上角、
//       (x2,y2) 为右下角的子矩阵的最大值。
//       数据范围：n, m <= 250，K <= 10^6，0 <= a[i][j] < 2^31。
//
// 算法：二维 ST 表。
//   记 st[a][b] 为「2^a 行 x 2^b 列」的方块最大值表：
//       st[a][b][i][j] = max{ a[i'][j'] : i <= i' < i + 2^a, j <= j' < j + 2^b }。
//   为省内存并保持缓存友好，不直接四象限递推，而是分成两步：
//     1) 行方向合并，得到只含行信息的 rowst[a] = st[a][0]；
//     2) 在 rowst[a] 上做列方向合并，依次得到 st[a][1], st[a][2], ...
//   询问 O(1)：设询问矩形有 Lx 行 Ly 列，令 a = floor(log2 Lx)、b = floor(log2 Ly)，
//   则四个角上的 2^a x 2^b 方块（左上、右上、左下、右下）恰好完全覆盖整个矩形，
//   取四者最大值即为答案。
//
// 复杂度：时间 O(n*m*log n*log m + K)，空间 O(n*m*log n*log m)。
//        本题 n=m=250 时预处理约 5e6 次取 max，查询 4 次查表，非常宽裕。
//
// 编译：/opt/homebrew/bin/g++-16 -O2 -std=c++17 -Wall -Wextra
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// ---------------- 快速读入 ----------------
static const int IBUF = 1 << 22;
static char ibuf[IBUF];
static int ilen = 0, ipos = 0;

static inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, IBUF, stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return (unsigned char)ibuf[ipos++];
}

// 读入一个非负整数（题面保证 0 <= a[i][j] < 2^31，int 足够）
static inline int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int v = 0;
    while (c >= '0' && c <= '9') {
        v = v * 10 + (c - '0');
        c = gc();
    }
    return v;
}

// ---------------- 快速输出 ----------------
static const int OBUF = 1 << 22;
static char obuf[OBUF];
static int opos = 0;

static inline void wch(char c) {
    if (opos == OBUF) {
        fwrite(obuf, 1, OBUF, stdout);
        opos = 0;
    }
    obuf[opos++] = c;
}

static inline void wInt(int v) {
    char tmp[12];
    int t = 0;
    if (v == 0) tmp[t++] = '0';
    while (v > 0) {
        tmp[t++] = (char)('0' + v % 10);
        v /= 10;
    }
    while (t > 0) wch(tmp[--t]);
    wch('\n');
}

// ---------------- 全局变量 ----------------
const int MAXN = 250;   // 行数上限
const int MAXM = 250;   // 列数上限
const int MAXL = 9;     // log2(250) + 1

int n, m, K;
int lg2[MAXM + 1];      // lg2[x] = floor(log2 x)

// tab[a * LB + b] 是一维展开（行优先）的 n x m 表，表示 2^a 行 x 2^b 列的方块最大值
vector<vector<int>> tab;
int LA, LB;

int main() {
    n = readInt();
    m = readInt();
    K = readInt();

    int mx = max(n, m);
    for (int i = 2; i <= mx; i++) lg2[i] = lg2[i >> 1] + 1;
    LA = lg2[n] + 1;
    LB = lg2[m] + 1;

    tab.assign((size_t)LA * LB, vector<int>());

    // 第 0 层：原矩阵
    vector<int> &base = tab[0];
    base.assign((size_t)n * m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) base[(size_t)i * m + j] = readInt();

    // 先做行方向合并：tab[a*LB + 0] 表示 2^a 行 x 1 列的最大值
    for (int a = 1; a < LA; a++) {
        vector<int> &cur = tab[(size_t)a * LB];
        cur.assign((size_t)n * m, 0);
        const vector<int> &prv = tab[(size_t)(a - 1) * LB];
        int half = 1 << (a - 1);
        int span = 1 << a;
        for (int i = 0; i + span <= n; i++) {
            const int *p0 = &prv[(size_t)i * m];
            const int *p1 = &prv[(size_t)(i + half) * m];
            int *pc = &cur[(size_t)i * m];
            for (int j = 0; j < m; j++) pc[j] = p0[j] > p1[j] ? p0[j] : p1[j];
        }
    }

    // 再做列方向合并：由 tab[a*LB + b-1] 得到 tab[a*LB + b]
    for (int a = 0; a < LA; a++) {
        for (int b = 1; b < LB; b++) {
            vector<int> &cur = tab[(size_t)a * LB + b];
            cur.assign((size_t)n * m, 0);
            const vector<int> &prv = tab[(size_t)a * LB + b - 1];
            int half = 1 << (b - 1);
            int span = 1 << b;
            for (int i = 0; i < n; i++) {
                const int *p0 = &prv[(size_t)i * m];
                int *pc = &cur[(size_t)i * m];
                for (int j = 0; j + span <= m; j++)
                    pc[j] = p0[j] > p0[j + half] ? p0[j] : p0[j + half];
            }
        }
    }

    // 逐问回答
    for (int q = 0; q < K; q++) {
        int x1 = readInt() - 1, y1 = readInt() - 1;
        int x2 = readInt() - 1, y2 = readInt() - 1;
        int lx = x2 - x1 + 1, ly = y2 - y1 + 1;
        int a = lg2[lx], b = lg2[ly];
        int rx = x2 - (1 << a) + 1;   // 下方方块的起始行（绝对行号，0 起）
        int dc = ly - (1 << b);       // 右方方块相对左上角方块的列偏移
        const vector<int> &t = tab[(size_t)a * LB + b];
        const int *r0 = &t[(size_t)x1 * m];
        const int *r1 = &t[(size_t)rx * m];
        int v = r0[y1];
        if (r0[y1 + dc] > v) v = r0[y1 + dc];
        if (r1[y1] > v) v = r1[y1];
        if (r1[y1 + dc] > v) v = r1[y1 + dc];
        wInt(v);
    }
    if (opos > 0) fwrite(obuf, 1, opos, stdout);
    return 0;
}
