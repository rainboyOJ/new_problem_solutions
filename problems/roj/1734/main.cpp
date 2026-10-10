/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:30
 * update_at: 2026-10-07 20:30
 */

// 一本通 1734《删边问题》（对应 roj 1734）
//
// 题意：无向图 n 个点 m 条边（点、边从 0 编号，允许重边与自环），Q 次询问，
//       每次给出边编号 x，问删掉这条边之后全图有多少个无序点对 (u, v) 互不可达，
//       答案模 1000 输出。
//
// 关键观察：删一条边只可能把「原本连通的那块」拆开，且只有该边是桥时连通性才变。
//   设该边所在连通块大小为 C，桥把 DFS 树子树部分（大小 s）与其余部分切开，
//   则新增互不可达点对 s * (C - s)；删非桥边（重边之一、自环、环上的边）答案不变。
//   于是 ans(x) = T0 + [x 是桥] * s * (C - s)，T0 = C(n,2) - Σ C(块大小,2)。
//
// 判定桥用 Tarjan：low[v] > dfn[u] 时树边 (u,v) 是桥。重边必须按「父边编号」跳过，
//   不能按「父顶点」跳过，否则两条平行边会互相看不到、被误判成桥。
//
// 复杂度 O(n + m + Q)；n,m,Q 最大 1e5/1e6/8e5，故 DFS 用显式栈迭代实现，防链状图爆栈。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100000 + 10;       // 点编号上界（题面 n <= 1e5）
const int MAXM = 1000000 + 10;      // 边编号上界（题面 m <= 1e6）
const int MAXARC = MAXM * 2 + 10;   // 每条无向边存两条弧

int n, m, Q;

// ---------------- 快速读入 / 输出（1e6 条边 + 8e5 次询问，cin 有超时风险）----------------
namespace FastIO {

const int BUFSIZE = 1 << 16;
char in_buf[BUFSIZE];
ll in_pos = 0, in_len = 0;

// 取一个字符；缓冲区空了就补一次读，文件结束返回 -1
int read_char() {
    if (in_pos == in_len) {
        in_len = fread(in_buf, 1, BUFSIZE, stdin);
        in_pos = 0;
        if (in_len <= 0) return -1;
    }
    return in_buf[in_pos++];
}

// 跳过空白后读一个非负整数
int read_int() {
    int c = read_char();
    while (c != -1 && (c < '0' || c > '9')) c = read_char();
    if (c == -1) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = read_char();
    }
    return x;
}

char out_buf[BUFSIZE];
int out_pos = 0;

void flush_out() {
    if (out_pos > 0) {
        fwrite(out_buf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

void write_char(char c) {
    if (out_pos == BUFSIZE) flush_out();
    out_buf[out_pos++] = c;
}

// 答案一定非负且已经模过 1000，逆序放数字再正序输出，末尾补换行
void write_int(ll x) {
    char tmp[8];
    int len = 0;
    if (x == 0) tmp[len++] = '0';
    while (x > 0) {
        tmp[len++] = '0' + x % 10;
        x /= 10;
    }
    while (len > 0) write_char(tmp[--len]);
    write_char('\n');
}

}  // namespace FastIO

// ---------------- 链式前向星：第 i 条输入边对应弧 2i 与 2i+1 ----------------
int head[MAXN];    // head[u] 是 u 的第一条出弧编号，-1 表示无边
int arc_to[MAXARC];  // 弧的终点
int arc_nxt[MAXARC]; // 同一起点的下一条弧
int arc_cnt = 0;

// 加一条无向边 u-v；第 i 条输入边的两条弧编号恰为 2i 与 2i+1
void add_edge(int u, int v) {
    arc_to[arc_cnt] = v;
    arc_nxt[arc_cnt] = head[u];
    head[u] = arc_cnt++;
    arc_to[arc_cnt] = u;
    arc_nxt[arc_cnt] = head[v];
    head[v] = arc_cnt++;
}

// ---------------- 并查集：求连通块大小，算 T0 ----------------
struct DsuNode {
    int fa;  // 父亲，根的父亲是自己
    int sz;  // 只在根上有效：连通块点数
};
DsuNode dsu[MAXN];

int find_root(int x) {
    while (dsu[x].fa != x) {
        dsu[x].fa = dsu[dsu[x].fa].fa;  // 路径折半
        x = dsu[x].fa;
    }
    return x;
}

void merge_node(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return;
    if (dsu[a].sz < dsu[b].sz) swap(a, b);
    dsu[b].fa = a;
    dsu[a].sz += dsu[b].sz;
}

// ---------------- 每个点在 DFS 树里的信息聚合在一起 ----------------
struct Vertex {
    int dfn;      // DFS 序，0 表示还没访问
    int low;      // 能回溯到的最小 dfn
    int pe;       // DFS 树中的父边编号，-1 表示是根
    int sub;      // DFS 树子树点数
    int it;       // 显式栈 DFS 的当前出弧指针
};
Vertex ver[MAXN];

int bridge_child[MAXM];  // 边编号 -> 它是桥时对应子树根；非桥保持 -1
int dfs_stack[MAXN];     // 显式栈（顶点编号），替代递归

ll unreachable0;  // T0：删边前全图互不可达的无序点对数

void read_input() {
    n = FastIO::read_int();
    m = FastIO::read_int();
    Q = FastIO::read_int();

    for (int i = 0; i < n; i++) {
        head[i] = -1;
        dsu[i].fa = i;
        dsu[i].sz = 1;
        ver[i].dfn = 0;
        ver[i].pe = -1;
    }
    for (int i = 0; i < m; i++) bridge_child[i] = -1;

    for (int i = 0; i < m; i++) {
        int u = FastIO::read_int();
        int v = FastIO::read_int();
        add_edge(u, v);          // 自环/重边原样保留，Tarjan 会正确处理
        merge_node(u, v);
    }
}

// T0 = C(n,2) - Σ 每个连通块 C(块大小,2)
void count_unreachable0() {
    unreachable0 = (ll)n * (n - 1) / 2;
    for (int i = 0; i < n; i++) {
        if (find_root(i) != i) continue;  // 只在根上统计一次
        ll s = dsu[i].sz;
        unreachable0 -= s * (s - 1) / 2;
    }
}

// 迭代式 Tarjan：求桥 + DFS 树子树大小。同一轮 DFS 里完成，二者和桥一一对应。
void find_bridges() {
    int timer = 0;
    for (int s = 0; s < n; s++) {
        if (ver[s].dfn != 0) continue;
        ver[s].dfn = ver[s].low = ++timer;
        ver[s].sub = 1;
        ver[s].it = head[s];
        int top = 0;
        dfs_stack[top++] = s;
        while (top > 0) {
            int u = dfs_stack[top - 1];
            int e = ver[u].it;
            if (e != -1) {
                ver[u].it = arc_nxt[e];
                int id = e >> 1;
                if (id == ver[u].pe) continue;  // 父边跳过：按边编号跳，重边才不会被误判成桥
                int v = arc_to[e];
                if (ver[v].dfn == 0) {
                    ver[v].dfn = ver[v].low = ++timer;
                    ver[v].pe = id;
                    ver[v].sub = 1;
                    ver[v].it = head[v];
                    dfs_stack[top++] = v;
                } else if (ver[v].dfn < ver[u].low) {
                    ver[u].low = ver[v].dfn;  // 返祖边（含重边指向祖先的那条）
                }
            } else {
                top--;  // u 的出弧走完，回溯到父亲 p
                if (top == 0) break;
                int p = dfs_stack[top - 1];
                ver[p].sub += ver[u].sub;
                if (ver[u].low < ver[p].low) ver[p].low = ver[u].low;
                // 子树 u 回不到 p 或更高处 → 父边是桥，子树 u 就是被切下来的一侧
                if (ver[u].low > ver[p].dfn) bridge_child[ver[u].pe] = u;
            }
        }
    }
}

void answer_queries() {
    for (int q = 0; q < Q; q++) {
        int x = FastIO::read_int();
        ll ans = unreachable0;
        int ch = bridge_child[x];
        if (ch >= 0) {
            ll c = dsu[find_root(ch)].sz;  // 该边所在连通块大小
            ll s = ver[ch].sub;            // 被切下来的子树大小
            ans += s * (c - s);
        }
        FastIO::write_int(ans % 1000);
    }
    FastIO::flush_out();
}

int main() {
    read_input();
    count_unreachable0();
    find_bridges();
    answer_queries();
    return 0;
}
