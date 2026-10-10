/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 22:29
 * update_at: 2026-10-07 22:29
 */
// main.cpp：一本通 1759《采访计划》。
// 把"管辖"关系建成一片森林：parent(i) = B_i 所有点的集合 LCA（不同树则 i 自成一棵新树），
// 长者 i 管辖的球长集合 S_i 恰好是森林里"根 -> i"这条路径上的全部点。
// 询问即求若⼲条根路径的并集大小：按 DFS 序排序后套虚树恒等式
//     |∪ 根路径| = Σ dep(v) - Σ dep(LCA(相邻同树点)) + (涉及的树棵数)。
// 与 main.py 是同一算法、同一复杂度。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;       // n, m <= 2e5
const int LOGN = 19;           // 2^18 = 262144 > 2e5，倍增表开 19 层留冗余
const int MAXQ = 2000005;      // 单个询问的元素数 <= Σsz <= 2e6

// 森林结点：par / dep / root / dfn 都是同一个点的属性，聚合成一个 struct
struct Node {
    int par;   // 森林中的直接父亲，0 表示它是所在树的根
    int dep;   // 深度，根为 0
    int root;  // 所在树的树根编号（编号等于树根，用于判断两点是否同树）
    int dfn;   // 真正的 DFS 先序编号，同一棵树内的点连续
};
Node node[MAXN];

int up[LOGN][MAXN];   // 倍增祖先表：up[j][u] 是 u 往上跳 2^j 步的祖先，根往上为 0
int head[MAXN];       // 孩子链表的头指针（链式前向星，只存每个点的一个孩子）
int nxt[MAXN];        // 同一父亲的下一个兄弟
int stk[MAXN];        // 迭代 DFS 的手写栈，避免链状树递归爆栈
int qbuf[MAXQ];       // 一个询问里的全部长者编号

// ------------------------------- 快速读入 -------------------------------
static char ibuf[1 << 20];
static size_t ipos = 0, ilen = 0;   // 缓冲区下标与已读长度，用 size_t 与 fread 的返回值对齐

inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;   // 输入读完了
    }
    return ibuf[ipos++];            // 输入只有数字与空白，char 转 int 不会出问题
}

inline int read_int() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x;
}

// ------------------------------- 快速输出 -------------------------------
static char obuf[1 << 20];
static size_t opos = 0;

inline void put_char(char c) {
    if (opos == sizeof(obuf)) { fwrite(obuf, 1, opos, stdout); opos = 0; }
    obuf[opos++] = c;
}

// 答案最大可达 Σdep ≈ 4e11，必须用 ll 输出
inline void write_ll(ll x) {
    char t[24];
    int k = 0;
    if (x == 0) t[k++] = '0';
    while (x > 0) {
        int d = x % 10;              // 收窄成 int，取值 0..9
        t[k++] = '0' + d;            // int 自动转 char 写入缓冲区
        x /= 10;
    }
    while (k > 0) put_char(t[--k]);
    put_char('\n');
}

// 求森林中两点的 LCA。保证调用时两点同树（深度差不为负）。
int lca(int a, int b) {
    if (node[a].dep < node[b].dep) swap(a, b);
    int d = node[a].dep - node[b].dep;
    for (int j = 0; d; ++j, d >>= 1) {          // 先把 a 抬到与 b 同深度
        if (d & 1) a = up[j][a];
    }
    if (a == b) return a;
    for (int j = LOGN - 1; j >= 0; --j) {       // 两个点一起往上跳，跳到 LCA 的儿子
        if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
    }
    return node[a].par;
}

// 询问里的点数按 DFS 序排序：排序后每一棵树的点各自连成一段
bool cmp_dfn(int a, int b) {
    return node[a].dfn < node[b].dfn;
}

int main() {
    int n = read_int();
    for (int i = 1; i <= n; ++i) {
        int sz = read_int();
        int cur = 0;             // B_i 中已合并部分的集合 LCA
        bool cross = false;      // B_i 的点分属不同树 ⇒ 交集为空 ⇒ i 自成一棵新树
        for (int j = 0; j < sz; ++j) {
            int k = read_int();
            if (j == 0) { cur = k; continue; }      // B_i 里的点都小于 i，必然已经建好
            if (cross) continue;                    // 已经判定跨树，剩下的点只需读完
            if (node[k].root != node[cur].root) { cross = true; continue; }
            cur = lca(cur, k);                      // 集合 LCA 只能相邻两点逐个合并
        }
        if (sz == 0 || cross) {     // S_i = {i}：i 是一棵新树的根
            node[i].par = 0;
            node[i].dep = 0;
            node[i].root = i;
        } else {                    // S_i = {i} ∪ (根 -> LCA(B_i) 的路径)
            node[i].par = cur;
            node[i].dep = node[cur].dep + 1;
            node[i].root = node[cur].root;
        }
        up[0][i] = node[i].par;
        for (int j = 1; j < LOGN; ++j) up[j][i] = up[j - 1][up[j - 1][i]];
        if (node[i].par) { nxt[i] = head[node[i].par]; head[node[i].par] = i; }
    }

    // 求真正的 DFS 先序：按 1..n 的顺序处理树根，每棵子树内的 dfn 连续
    int timer = 0;
    for (int i = 1; i <= n; ++i) {
        if (node[i].par) continue;
        int top = 0;
        stk[top++] = i;
        while (top) {
            int u = stk[--top];
            node[u].dfn = ++timer;
            for (int c = head[u]; c; c = nxt[c]) stk[top++] = c;
        }
    }

    int m = read_int();
    for (int qi = 0; qi < m; ++qi) {
        int sz = read_int();
        for (int j = 0; j < sz; ++j) qbuf[j] = read_int();
        if (sz == 0) { write_ll(0); continue; }     // 空询问：没有任何球长被采访
        sort(qbuf, qbuf + sz, cmp_dfn);
        ll ans = node[qbuf[0]].dep;     // 第一条根路径的长度（不含根，故直接用 dep）
        int trees = 1;                  // 涉及的树棵数，DFS 序下同树的点必连续
        for (int j = 1; j < sz; ++j) {
            int u = qbuf[j - 1], v = qbuf[j];
            ans += node[v].dep;
            if (node[u].root != node[v].root) trees++;      // 跨树：两段根路径不相交
            else ans -= node[lca(u, v)].dep;                // 同树：减去重复计数的公共前缀
        }
        ans += trees;                   // 每棵树的根在最浅处只算一次
        write_ll(ans);
    }

    if (opos) fwrite(obuf, 1, opos, stdout);
    return 0;
}
