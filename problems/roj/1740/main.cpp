/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 22:05
 * update_at: 2026-10-07 22:27
 */
// main.cpp：一本通 1740《星空穿越》
// 题意：n 点 m 边的无向简单图，每条边带奇偶标记 c；用尽量少的行走使每条边被走过的总次数 ≡ c (mod 2)。
// 结论：设 S = {c=1 的边}，对每个连通块 C 记 T_C = S∩C 中度数为奇数的点集，则
//       K_min = Σ_C ( |T_C| > 0 ? |T_C|/2 : [S_C 非空] )。
// 构造：块内取生成树、每条树边放 2 份（只加连通性、不改奇偶），再放入 S_C 的全部边；
//       若 T_C 非空，额外加一个虚点 X 与 T_C 各点相连，此时全图偶度且连通，
//       从 X 出发求欧拉回路，按 X 出现的位置切开，恰得 |T_C|/2 条路径。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;    // 单组点数上限（题面 n ≤ 2×10^5，留足余量）
const int MAXM = 500005;    // 单组边数上限（题面 m ≤ 2×10^5，留足余量）
const int MAXME = 2000005;  // 辅助图 M 的边数上限：m + 2(n-1) + n 最坏约 2×10^6
const int MAXARC = 4000010; // M 的半边数上限
const int BUF_IN = 1 << 25; // 输入缓冲：整份数据一次读入（题面 Σn,Σm ≤ 5×10^5，最大约 10MB）
const int BUF_OUT = 1 << 22;

/* ── 输入：整块 fread + 手写整数解析 ── */
char in_buf[BUF_IN];
int in_len, in_pos;

inline int read_int() {
    if (in_pos >= in_len) return -1;
    int c = (unsigned char)in_buf[in_pos++];
    while (c <= ' ' && in_pos < in_len) c = (unsigned char)in_buf[in_pos++];
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        if (in_pos >= in_len) break;
        c = (unsigned char)in_buf[in_pos++];
    }
    return x;
}

/* ── 输出：整块缓冲 ── */
char out_buf[BUF_OUT];
int out_pos;

inline void out_flush() {
    if (out_pos) { fwrite(out_buf, 1, out_pos, stdout); out_pos = 0; }
}
inline void out_ch(char ch) {
    if (out_pos == BUF_OUT) out_flush();
    out_buf[out_pos++] = ch;
}
inline void out_int(ll x) {
    char tmp[24];
    int t = 0;
    if (x == 0) tmp[t++] = '0';
    while (x > 0) { tmp[t++] = (char)('0' + x % 10); x /= 10; }
    while (t > 0) out_ch(tmp[--t]);
}
inline void out_endl() { out_ch('\n'); }

/* ── 原图数据 ── */
int n, m;                      // 本组的点数与边数
int eu[MAXM], ev[MAXM], ec[MAXM]; // 第 i 条边：两端点（0 起）与奇偶标记
int sdeg[MAXN];                // sdeg[v] = 与 v 相邻的 S 边条数 mod 2

struct MEdge { int a, b; };    // 辅助图 M 的一条边（顶点为块内局部编号，虚点编号为 nC）

/* ── 原图 CSR 邻接：范围内按边的输入顺序排列，与生成树的遍历顺序一致 ── */
int g_off[MAXN + 1], g_to[2 * MAXM], g_eid[2 * MAXM];
int g_cur[MAXN];

/* ── 连通块与生成树 ── */
int comp[MAXN];                // 每个点所属连通块编号
int par_eid[MAXN];             // 生成树上每个点的父边编号（根为 -1）
int order_v[MAXN];             // 全部点按「连通块号 + 块内出栈顺序」排列
int vert_beg[MAXN + 1];        // 第 c 块的点占据 order_v[vert_beg[c], vert_beg[c+1])
int ncomp;

int eid_beg[MAXN + 1], eid_ord[MAXM], eid_cur[MAXN + 1]; // 边按连通块分组（块内保持输入顺序）
char has_s[MAXN];              // 第 c 块是否含有 c=1 的边

/* ── 辅助图 M：CSR 邻接 + 迭代欧拉回路 ── */
MEdge me[MAXME];
int m_off[MAXN + 1], m_cur[MAXN + 1];
int m_nbr[MAXARC], m_twin[MAXARC]; // 每条半边：对端顶点、镜像半边所在位置
char m_used[MAXARC];
int stack_v[MAXN];             // DFS 栈（原图）
int stack_e[MAXARC];           // 欧拉回路的 vertex 栈
int seq[MAXARC];               // 欧拉回路的顶点序列（逆序存放后原地反转）

int loc[MAXN], loc_vert[MAXN]; // 原图点 -> 块内局部编号；局部编号 -> 原图点
ll total_k;                    // 本组的答案 K

// 把一条边写进原图 CSR 边表的指定槽位（槽位由调用方按输入顺序分配）。
void fill_g_edge(int v, int eid, int pos) {
    g_to[pos] = v;
    g_eid[pos] = eid;
}

// 划分连通块并为每块记录出栈顺序、父边（决定生成树）。
void build_components() {
    ncomp = 0;
    int vcnt = 0;
    for (int s = 0; s < n; s++) {
        if (comp[s] != -1) continue;
        vert_beg[ncomp] = vcnt;
        comp[s] = ncomp;
        par_eid[s] = -1; // 生成树的根没有父边
        int sp = 0;
        stack_v[sp++] = s;
        while (sp) {
            int v = stack_v[--sp];
            order_v[vcnt++] = v;
            for (int p = g_off[v]; p < g_off[v + 1]; p++) {
                int to = g_to[p];
                if (comp[to] == -1) {
                    comp[to] = ncomp;
                    par_eid[to] = g_eid[p];
                    stack_v[sp++] = to;
                }
            }
        }
        ncomp++;
    }
    vert_beg[ncomp] = vcnt;
}

// 统计边的分组（按连通块）与每块是否含 S 边：两者都只扫描一遍边表。
void group_edges() {
    for (int c = 0; c <= ncomp; c++) eid_beg[c] = 0;
    for (int i = 0; i < m; i++) eid_beg[comp[eu[i]] + 1]++;
    for (int c = 0; c < ncomp; c++) eid_beg[c + 1] += eid_beg[c];
    for (int c = 0; c <= ncomp; c++) eid_cur[c] = eid_beg[c];
    for (int i = 0; i < m; i++) eid_ord[eid_cur[comp[eu[i]]]++] = i;
    for (int c = 0; c < ncomp; c++) has_s[c] = 0;
    for (int i = 0; i < m; i++)
        if (ec[i]) has_s[comp[eu[i]]] = 1;
}

// 迭代 Hierholzer：从 base 出发求 M 的欧拉回路，结果按逆序写进 seq 再原地反转。
void euler_circuit(int base, int mvtx, int &seq_cnt) {
    int sp = 0;
    seq_cnt = 0;
    for (int v = 0; v < mvtx; v++) m_cur[v] = m_off[v];
    stack_e[sp++] = base;
    while (sp) {
        int v = stack_e[sp - 1];
        int chosen = -1;
        while (m_cur[v] < m_off[v + 1]) {
            int p = m_cur[v]++;
            if (!m_used[p]) { chosen = p; break; } // 取 v 邻接表里第一条未走过的半边
        }
        if (chosen < 0) {                           // v 已经无路可走：记进回路并回退
            seq[seq_cnt++] = v;
            sp--;
        } else {
            m_used[chosen] = 1;
            m_used[m_twin[chosen]] = 1;             // 同一条边的两个方向一起标记
            stack_e[sp++] = m_nbr[chosen];
        }
    }
    for (int i = 0, j = seq_cnt - 1; i < j; i++, j--) {
        int t = seq[i]; seq[i] = seq[j]; seq[j] = t;
    }
}

// 输出第 c 块的一条路径：seq[l..r] 是块内局部编号，输出时换算回原图编号。
void print_path(int l, int r, int seq_cnt) {
    out_int(r - l + 1);
    for (int i = l; i <= r; i++) {
        out_ch(' ');
        out_int(loc_vert[seq[i]] + 1);
    }
    out_endl();
}

// 处理一个连通块：构造 M、求欧拉回路、切开输出。
void solve_comp(int c) {
    int beg = vert_beg[c], end = vert_beg[c + 1];
    int nC = end - beg;
    int nT = 0;
    for (int i = beg; i < end; i++) if (sdeg[order_v[i]]) nT++;
    if (!has_s[c]) return; // 该块没有任何 c=1 的边，不需要安排人

    for (int i = beg; i < end; i++) {
        loc[order_v[i]] = i - beg;
        loc_vert[i - beg] = order_v[i];
    }

    int me_cnt = 0;
    // (1) 生成树的每条树边放 2 份：既保证 M 连通，又不会改变任何点的度数奇偶
    for (int i = beg; i < end; i++) {
        int v = order_v[i];
        int pe = par_eid[v];
        if (pe < 0) continue;
        int u = (eu[pe] == v) ? ev[pe] : eu[pe];
        me[me_cnt].a = loc[u]; me[me_cnt].b = loc[v]; me_cnt++;
        me[me_cnt].a = loc[u]; me[me_cnt].b = loc[v]; me_cnt++;
    }
    // (2) S_C 的全部边各放 1 份：这就是必须被走成奇数次的那部分
    for (int k = eid_beg[c]; k < eid_beg[c + 1]; k++) {
        int i = eid_ord[k];
        if (!ec[i]) continue;
        me[me_cnt].a = loc[eu[i]]; me[me_cnt].b = loc[ev[i]]; me_cnt++;
    }
    // (3) 奇数度点各接一条虚点边：让虚点成为唯一"多出来"的拐点
    int xv = (nT > 0) ? nC : -1;
    if (xv >= 0) {
        for (int i = beg; i < end; i++)
            if (sdeg[order_v[i]]) { me[me_cnt].a = xv; me[me_cnt].b = i - beg; me_cnt++; }
    }

    // 建 M 的 CSR 邻接：半边 2i 落在第 i 条边 a 端的区间里，半边 2i+1 落在 b 端，
    // 每个顶点的邻接区间内保持边的构造顺序（与生成路径的顺序一致）。
    int mvtx = nC + (xv >= 0 ? 1 : 0);
    for (int v = 0; v <= mvtx; v++) m_off[v] = 0;
    for (int i = 0; i < me_cnt; i++) { m_off[me[i].a + 1]++; m_off[me[i].b + 1]++; }
    for (int v = 0; v < mvtx; v++) m_off[v + 1] += m_off[v];
    for (int v = 0; v <= mvtx; v++) m_cur[v] = m_off[v];
    for (int i = 0; i < me_cnt; i++) {
        int a = me[i].a, b = me[i].b;
        int p = m_cur[a]++, q = m_cur[b]++;
        m_nbr[p] = b; m_twin[p] = q;
        m_nbr[q] = a; m_twin[q] = p;
    }
    for (int i = 0; i < 2 * me_cnt; i++) m_used[i] = 0;

    int seq_cnt = 0;
    euler_circuit(xv >= 0 ? xv : 0, mvtx, seq_cnt);

    if (xv < 0) {
        // T_C = ∅：M 本身就是欧拉图，整条回路就是 1 条行走（首尾同点需要重复输出一次）
        out_int(seq_cnt);
        for (int i = 0; i < seq_cnt; i++) { out_ch(' '); out_int(loc_vert[seq[i]] + 1); }
        out_endl();
    } else {
        // T_C ≠ ∅：回路里每两次经过虚点之间就是一条路径，虚点自身不输出
        int prev = 0; // seq[0] == 虚点
        for (int i = 1; i < seq_cnt; i++) {
            if (seq[i] != xv) continue;
            if (prev + 1 <= i - 1) print_path(prev + 1, i - 1, seq_cnt);
            prev = i;
        }
    }
}

int main() {
    in_len = (int)fread(in_buf, 1, sizeof(in_buf), stdin);
    in_pos = 0;
    int T = read_int();
    if (T < 0) { out_flush(); return 0; }

    for (int tc = 0; tc < T; tc++) {
        n = read_int();
        m = read_int();
        for (int v = 0; v < n; v++) { comp[v] = -1; sdeg[v] = 0; g_off[v] = 0; }
        g_off[n] = 0;

        for (int i = 0; i < m; i++) {
            int a = read_int() - 1, b = read_int() - 1, c = read_int();
            eu[i] = a; ev[i] = b; ec[i] = c;
            sdeg[a] ^= c; sdeg[b] ^= c; // 度数的奇偶：每条相邻的 S 边各翻转一次
        }

        // 原图 CSR：先数度数，再按边的输入顺序填边表
        for (int i = 0; i < m; i++) { g_off[eu[i] + 1]++; g_off[ev[i] + 1]++; }
        for (int v = 0; v < n; v++) g_off[v + 1] += g_off[v];
        for (int v = 0; v < n; v++) g_cur[v] = g_off[v];
        for (int i = 0; i < m; i++) {
            int p = g_cur[eu[i]]++, q = g_cur[ev[i]]++;
            fill_g_edge(ev[i], i, p);
            fill_g_edge(eu[i], i, q);
        }

        build_components();
        group_edges();

        // 第一遍：只算答案 K
        total_k = 0;
        for (int c = 0; c < ncomp; c++) {
            if (!has_s[c]) continue;
            int nT = 0;
            for (int i = vert_beg[c]; i < vert_beg[c + 1]; i++)
                if (sdeg[order_v[i]]) nT++;
            total_k += (nT > 0) ? (nT / 2) : 1;
        }
        out_int(total_k); out_endl();

        // 第二遍：逐块构造并输出路径
        for (int c = 0; c < ncomp; c++) {
            if (!has_s[c]) continue;
            solve_comp(c);
        }
    }

    out_flush();
    return 0;
}
