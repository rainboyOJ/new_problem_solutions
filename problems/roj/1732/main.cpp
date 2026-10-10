/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:38
 * update_at: 2026-10-07 20:38
 */
// ROJ 1732《情报传递》  C++17（/opt/homebrew/bin/g++-16 -O2 编译）
// 限制：time 2000 ms / memory 256 MB
// ----------------------------------------------------------------------------
// 【题意】两类「要求」：① a 必须能到达 b；② a 必须不能到达 b（保证 a≠b）。
//         要求构造一个有向图（电话线）满足全部要求，或判定无解；
//         边的条数 P 需满足 P ≤ n+m+t。
// 【核心结论】
//   设 R1 = 全部①要求连成的边集，TC(R1) 为其传递闭包。对任意合法图 G：
//   每条①(a,b) 都要求 a⇝b ∈ G，而可达性传递 ⇒ 归纳得 TC(R1) ⊆ Reach(G)。于是
//     • 若有②(a,b) 满足 a⇝b ∈ TC(R1)，则任何 G 都违反② ⇒ NO；
//     • 否则取 G = R1 即合法：①的每条要求都成了 1 条边，②要求的点对恰好是
//       TC(R1) 里不存在的那些 ⇒ 全部满足 ⇒ YES，且 P = m1 ≤ n+m+t 恒成立。
//   ⇒ 判定归结为：在「①要求图」上判断这 t 个点对是否可达。
// 【算法】
//   1. 迭代式 Tarjan 求 SCC（n=1e5 的链也不爆栈；不用递归、不动栈限制）。
//      弹栈顺序保证跨分量边 u→v 必有 comp[u] > comp[v]，故按分量编号**升序**
//      递推即为「后继先算好」的正确顺序，无需另做拓扑排序。
//   2. ②的 a、b 落在同一分量 ⇒ 同属一个 SCC、互相可达 ⇒ 立即 NO（快速判据）。
//   3. 缩点得 DAG（去掉自环、跨分量边排序去重后建 CSR）。在 DAG 上做**分块
//      bitset** 可达性：位空间 = 分量编号，一块 W 个分量，每行 W/64 个 u64，
//      row[c] = bit(c-lo) | ∪ row[d]（c→d 为跨分量边）。②询问按目标分量计数排序，
//      每块算完就地回答本块的询问；任何违例立即 NO 返回。
//      位运算量 ≈ Σ_blocks (C + E)·W/64 = O((C+E)·C/64)，行内存 C·W/8 字节。
// 【样例】样例1 → NO；样例2 → YES / 2 / (1 2) (2 3)，与题面逐字节一致。
// ----------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;  // n 的上限
const int BLK = 4096;     // 可达性 bitset 的分块宽度（每块覆盖 BLK 个分量）
const int BLKW = BLK / 64;

// ------------------------------ 快速输入输出 ------------------------------
namespace io {
const int SZ = 1 << 20;
char buf[SZ];
int len = 0, pos = 0;
inline int gc() {
    if (pos == len) {
        len = (int)fread(buf, 1, SZ, stdin);
        pos = 0;
        if (len <= 0) return -1;
    }
    return buf[pos++];
}
inline int readInt() {
    int c = gc();
    while (c <= ' ' && c != -1) c = gc();
    int x = 0;
    while (c > ' ') { x = x * 10 + (c - '0'); c = gc(); }
    return x;
}
inline void writes(const char* s) { fwrite(s, 1, strlen(s), stdout); }
}  // namespace io

struct Arc {  // 缩点 DAG 上的一条跨分量边，排序去重时按 (from, to) 比较
    int from;
    int to;
};

// 给 Arc 排序用的比较器（不用 lambda，便于阅读与调试）
bool arcLess(const Arc& x, const Arc& y) {
    if (x.from != y.from) return x.from < y.from;
    return x.to < y.to;
}

int n, m, t;
vector<int> adj[MAXN];   // ① 要求连成的有向图
int ea[MAXN], eb[MAXN];  // ① 要求的端点（YES 时原样输出成电话线）
int qa[MAXN], qb[MAXN];  // ② 要求的端点

int dfn[MAXN], low[MAXN], comp[MAXN], edgePtr[MAXN], compSize[MAXN];
int dfsStk[MAXN], stk[MAXN];  // dfsStk = 迭代 DFS 调用栈，stk = Tarjan 栈
unsigned char onstk[MAXN];

// 迭代式 Tarjan：返回强连通分量数。
// 编号规则：跨分量边 u→v 必有 comp[u] > comp[v]（弹栈顺序即 DAG 的逆拓扑序）。
int tarjan() {
    int timer = 0, cc = 0, top = 0;
    for (int s = 1; s <= n; s++) {
        if (dfn[s]) continue;
        dfn[s] = low[s] = ++timer;
        stk[top++] = s;
        onstk[s] = 1;
        int ctop = 0;
        dfsStk[ctop++] = s;
        while (ctop) {
            int u = dfsStk[ctop - 1];
            if (edgePtr[u] < (int)adj[u].size()) {
                int v = adj[u][edgePtr[u]++];
                if (!dfn[v]) {
                    dfn[v] = low[v] = ++timer;
                    stk[top++] = v;
                    onstk[v] = 1;
                    dfsStk[ctop++] = v;
                } else if (onstk[v] && dfn[v] < low[u]) {
                    low[u] = dfn[v];  // 回边：用 dfn 更新 low
                }
            } else {
                ctop--;
                if (low[u] == dfn[u]) {  // u 是所在 SCC 的根 → 弹栈定型
                    while (true) {
                        int w = stk[--top];
                        onstk[w] = 0;
                        comp[w] = cc;
                        if (w == u) break;
                    }
                    cc++;
                }
                if (ctop) {  // 把子孙的 low 回传给父节点
                    int p = dfsStk[ctop - 1];
                    if (low[u] < low[p]) low[p] = low[u];
                }
            }
        }
    }
    return cc;
}

Arc arcs[MAXN];                    // 跨分量边（去重前）
int dagStart[MAXN + 1];            // CSR：分量 c 的出边在 dagTo[dagStart[c] .. dagStart[c+1])
int dagTo[MAXN];
int order[MAXN];                   // ②询问按目标分量排序后的下标序列
int bucket[MAXN];                  // 计数排序用的桶头

int main() {
    n = io::readInt();
    m = io::readInt();
    for (int i = 1; i <= m; i++) {
        int a = io::readInt(), b = io::readInt();
        ea[i] = a;
        eb[i] = b;
        adj[a].push_back(b);
    }
    t = io::readInt();
    for (int i = 1; i <= t; i++) { qa[i] = io::readInt(); qb[i] = io::readInt(); }

    int C = tarjan();
    for (int i = 1; i <= n; i++) compSize[comp[i]]++;

    // 快速判据：②的 a、b 落在同一分量 ⇒ 同一 SCC 内互相可达 ⇒ 必违反②
    //（题面保证 a≠b；a==b 时只有大小 > 1 的分量才必然可达）
    bool bad = false;
    for (int i = 1; i <= t && !bad; i++)
        if (comp[qa[i]] == comp[qb[i]] && (qa[i] != qb[i] || compSize[comp[qa[i]]] > 1))
            bad = true;

    // ---- 缩点 DAG：收集跨分量边，排序去重，建 CSR ----
    int acnt = 0;
    for (int i = 1; i <= m; i++) {
        int ca = comp[ea[i]], cb = comp[eb[i]];
        if (ca != cb) { arcs[acnt].from = ca; arcs[acnt].to = cb; acnt++; }
    }
    sort(arcs, arcs + acnt, arcLess);
    int E = 0;
    for (int i = 0; i < acnt; i++)
        if (i == 0 || arcs[i].from != arcs[i - 1].from || arcs[i].to != arcs[i - 1].to)
            arcs[E++] = arcs[i];  // 就地压缩：每条 (from,to) 只留一次
    for (int c = 0; c <= C; c++) dagStart[c] = 0;
    for (int i = 0; i < E; i++) dagStart[arcs[i].from + 1]++;
    for (int c = 0; c < C; c++) dagStart[c + 1] += dagStart[c];
    for (int c = 0; c < C; c++) bucket[c] = dagStart[c];  // 借用成填充指针
    for (int i = 0; i < E; i++) {
        int c = arcs[i].from;
        dagTo[bucket[c]++] = arcs[i].to;
    }

    // ---- ②询问按「目标分量」计数排序（目标分量是 [0,C) 内的整数）----
    for (int c = 0; c <= C; c++) bucket[c] = 0;
    for (int i = 1; i <= t; i++) order[comp[qb[i]]]++;
    {
        int acc = 0;
        for (int c = 0; c < C; c++) {
            int cnt = order[c];
            order[c] = acc;
            acc += cnt;
        }
        order[C] = acc;
    }
    for (int i = 1; i <= t; i++) bucket[order[comp[qb[i]]]++] = i;
    for (int i = 1; i <= t; i++) order[i] = bucket[i - 1];  // order[1..t] 即排序结果

    int qptr = 1;
    if (!bad) {
        vector<unsigned long long> reach((size_t)C * BLKW, 0);  // 约 C·BLK/8 字节
        for (int lo = 0; lo < C; lo += BLK) {
            int hi = min(C, lo + BLK);  // 本块追踪的目的地区间 [lo, hi)
            // 整块清零：编号 < lo 的行在本块必须是全 0
            //（跨分量边恒从大编号指向小编号，从 < lo 出发到不了 >= lo 的点）。
            memset(reach.data(), 0, sizeof(unsigned long long) * (size_t)C * BLKW);
            // 分量编号升序递推：c 的后继编号都更小，所以后继在本块已经算好
            for (int c = lo; c < C; c++) {
                unsigned long long* row = &reach[(size_t)c * BLKW];
                if (c < hi) row[(c - lo) >> 6] |= 1ULL << ((c - lo) & 63);
                for (int e = dagStart[c]; e < dagStart[c + 1]; e++) {
                    const unsigned long long* sr = &reach[(size_t)dagTo[e] * BLKW];
                    for (int w = 0; w < BLKW; w++) row[w] |= sr[w];
                }
            }
            // 本块内回答所有「目标落在 [lo,hi)」的询问
            while (qptr <= t && comp[qb[order[qptr]]] < hi) {
                int i = order[qptr++];
                // a==b 的询问已由上面的快速判据处理（看分量大小），此处跳过
                if (qa[i] == qb[i]) continue;
                int cb = comp[qb[i]] - lo;
                int ca = comp[qa[i]];
                if ((reach[(size_t)ca * BLKW + (cb >> 6)] >> (cb & 63)) & 1ULL) {
                    bad = true;
                    break;
                }
            }
            if (bad) break;
        }
    }

    // ---- 输出 ----
    if (bad) {
        io::writes("NO\n");
        return 0;
    }
    // G0 自己就是合法解：m 条①要求原样当电话线输出，P = m ≤ n+m+t
    io::writes("YES\n");
    printf("%d\n", m);
    for (int i = 1; i <= m; i++) printf("%d %d\n", ea[i], eb[i]);
    return 0;
}
