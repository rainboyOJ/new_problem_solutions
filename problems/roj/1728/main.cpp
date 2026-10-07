/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 19:16
 * update_at: 2026-10-07 19:16
 */

// 一本通 1728《构造序列》（与洛谷 P3588 [POI2015] Pustynia 同题）
//
// 把每条信息翻译成差分约束：边 u -> v 权 w 表示 a[v] >= a[u] + w。
//   * 线段树：儿子 -> 父亲 权 0（父亲代表区间内所有位置的最大下界）
//   * 每条信息新建一个条件点 p，含义是“x 集合里的最小值”：
//       - 区间内所有“剩下的位置”的线段树节点 -> p 权 1（它们都严格小于该最小值）
//       - p -> 每个 x_i 权 0（x_i 不低于该最小值）
//   * 已知位置直接以 d 作为下界；其余没有任何入边的点下界取 1
// 然后按拓扑序把下界往出边推，得到每个位置的最小可行取值。
// 无解的三种情况：约束成环、某个下界超过 1e9、已知位置的下界超过给定的 d。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LIMIT = 1000000000;  // 值域上界，任何位置的下界超过它就没有合法方案

// ---------------- 快速读入 ----------------
static char ibuf[1 << 20];
static int ipos = 0, ilen = 0;

// 从 1MB 缓冲区里取下一个字符；缓冲区空了就再读一块，读到文件尾返回 -1。
int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return ibuf[ipos++];
}

// 读入一个正整数（题面输入只有正整数和空白字符）。
int read_int() {
    int c = gc();
    while (c < '0' || c > '9') c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int n, s, m;    // 序列长度、已知位置个数、信息条数
int sz;         // 线段树叶子数：>= n 的最小 2 的幂，位置 i 的叶子编号是 sz + i - 1
int segN;       // 线段树节点编号 1 .. segN-1（segN = 2*sz）
int V;          // 图中总点数：线段树节点 + 条件点，条件点编号 segN .. segN+m-1

vector<int> known;  // known[u] = 位置叶子 u 已知的精确值，0 表示未知；非叶子恒为 0
vector<int> ql, qr; // 每条信息的左右端点 l、r
vector<int> xs;     // 所有信息里给出的 x 扁平存储（题面保证每条内部递增）
vector<int> xoff;   // xoff[q] = 第 q 条信息的 x 在 xs 中的起始下标

// 链式前向星：head[u] 为 u 的第一条出边编号（0 表示没有），nxt 串起同一出点的边。
// 边权只有 0/1，且恰好由终点类型决定：指向条件点（编号 >= segN）的边权为 1
// （那就是“严格大于”贡献的 +1），指向线段树节点的边权为 0。
// 利用这一点省掉单独的边权数组，最坏数据下常驻内存能压进 128MB。
struct Edge {
    int to;    // 终点
    int nxt;   // 同起点的下一条边
};
vector<int> head;
vector<Edge> e;
int edgeCnt;
vector<int> indeg;  // 每个点的入度，拓扑排序用

int rangeBuf[40];   // 一次区间分解得到的线段树节点编号（最多 2*log2(1e5) < 40 个）
int rangeCnt;

// 把 1-indexed 闭区间 [l, r] 分解成 O(log n) 个线段树节点，结果写入 rangeBuf。
// l > r（空区间）时 rangeCnt 为 0。
void decompose_range(int l, int r) {
    rangeCnt = 0;
    int lo = l - 1 + sz;
    int hi = r - 1 + sz + 1;
    while (lo < hi) {
        if (lo & 1) rangeBuf[rangeCnt++] = lo++;
        if (hi & 1) rangeBuf[rangeCnt++] = --hi;
        lo >>= 1;
        hi >>= 1;
    }
}

// 加一条 u -> v 的边，权重按终点类型判定（见 Edge 上方注释）。
void add_edge(int u, int v) {
    edgeCnt++;
    e[edgeCnt].to = v;
    e[edgeCnt].nxt = head[u];
    head[u] = edgeCnt;
    indeg[v]++;
}

int main() {
    n = read_int();
    s = read_int();
    m = read_int();

    sz = 1;
    while (sz < n) sz <<= 1;
    segN = 2 * sz;
    V = segN - 1 + m;

    known.assign(V + 1, 0);
    for (int i = 0; i < s; i++) {
        int p = read_int();
        int d = read_int();
        known[sz + p - 1] = d;  // 已知位置：a[p] 的精确值就是 d
    }

    ql.assign(m, 0);
    qr.assign(m, 0);
    xoff.assign(m + 1, 0);
    xs.reserve(300005);
    for (int q = 0; q < m; q++) {
        ql[q] = read_int();
        qr[q] = read_int();
        int k = read_int();
        xoff[q] = (int)xs.size();
        for (int j = 0; j < k; j++) xs.push_back(read_int());
    }
    xoff[m] = (int)xs.size();

    // 第一遍：只统计边数，好把 vector 一次性开够，避免反复扩容。
    ll cnt = 2LL * sz - 2;   // 儿子 -> 父亲
    cnt += (ll)xs.size();    // 条件点 -> 每个 x_i
    for (int q = 0; q < m; q++) {
        int prev = ql[q];
        for (int j = xoff[q]; j < xoff[q + 1]; j++) {
            decompose_range(prev, xs[j] - 1);  // x_j 之前的那段空隙
            cnt += rangeCnt;
            prev = xs[j] + 1;
        }
        decompose_range(prev, qr[q]);          // 最后一个 x 之后的空隙
        cnt += rangeCnt;
    }

    head.assign(V + 1, 0);
    indeg.assign(V + 1, 0);
    e.resize((size_t)cnt + 1);
    edgeCnt = 0;

    // 第二遍：真正建图。
    for (int i = 2; i < segN; i++) add_edge(i, i >> 1);  // 儿子 -> 父亲，权 0

    for (int q = 0; q < m; q++) {
        int p = segN + q;  // 条件点：含义是“x 集合中的最小值”
        int prev = ql[q];
        for (int j = xoff[q]; j < xoff[q + 1]; j++) {
            int x = xs[j];
            decompose_range(prev, x - 1);  // 剩下的位置 -> p，权 1（严格大于）
            for (int t = 0; t < rangeCnt; t++) add_edge(rangeBuf[t], p);
            add_edge(p, sz + x - 1);       // p -> x_i，权 0
            prev = x + 1;
        }
        decompose_range(prev, qr[q]);
        for (int t = 0; t < rangeCnt; t++) add_edge(rangeBuf[t], p);
    }

    // 拓扑排序递推下界：val[u] = max(val[u], val[pre] + w)。
    vector<int> val(V + 1, 0);
    vector<int> que;
    que.reserve(V);
    for (int i = 1; i <= n; i++) {
        int leaf = sz + i - 1;
        if (known[leaf]) val[leaf] = known[leaf];  // 已知位置以精确值为下界
    }
    for (int u = 1; u <= V; u++) {
        if (indeg[u] == 0) {
            if (val[u] < 1) val[u] = 1;  // 没有任何约束的点取最小值 1
            que.push_back(u);
        }
    }

    bool bad = false;
    for (int qi = 0; qi < (int)que.size(); qi++) {
        int u = que[qi];
        if (val[u] > LIMIT) {          // 下界超出值域，无解
            bad = true;
            break;
        }
        if (known[u] && val[u] > known[u]) {  // 已知位置被迫大于 d，矛盾
            bad = true;
            break;
        }
        for (int ei = head[u]; ei != 0; ei = e[ei].nxt) {
            int v = e[ei].to;
            int w = (v >= segN) ? 1 : 0;
            if (val[v] < val[u] + w) val[v] = val[u] + w;
            if (--indeg[v] == 0) que.push_back(v);
        }
    }

    if (!bad) {
        for (int u = 1; u <= V; u++) {
            if (indeg[u] > 0) {  // 还有没被剥掉的点，说明约束成环
                bad = true;
                break;
            }
        }
    }

    if (bad) {
        puts("NIE");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        int v = val[sz + i - 1];
        if (v < 1 || v > LIMIT) {
            bad = true;
            break;
        }
    }
    if (bad) {
        puts("NIE");
        return 0;
    }

    // 输出：每个位置取它的下界即为可行解。
    puts("TAK");
    static char obuf[1 << 22];
    int op = 0;
    for (int i = 1; i <= n; i++) {
        int x = val[sz + i - 1];
        char tmp[12];
        int t = 0;
        if (x == 0) tmp[t++] = '0';
        while (x > 0) {
            tmp[t++] = char('0' + x % 10);
            x /= 10;
        }
        while (t > 0) obuf[op++] = tmp[--t];
        obuf[op++] = (i == n) ? '\n' : ' ';
    }
    fwrite(obuf, 1, op, stdout);

    return 0;
}
