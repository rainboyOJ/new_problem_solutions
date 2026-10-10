/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:29
 * update_at: 2026-10-07 20:29
 */
// main.cpp：一本通 1731《最大流》（同 CERC 2015 J "Juice Junctions"）
// 无向图每个点度数 <= 3、每条边容量 1，求所有点对 i<j 间最大流之和。
// 由最大流最小割定理：端点度为 d 的点对流不超过 min(d(u),d(v)) <= 3，故流量 ∈ {0,1,2,3}。
//   flow >= 1 <=> 两点在原图中连通（并查集）；
//   flow >= 2 <=> 两点属于同一「边双连通分量」（删掉桥以后的块）；
//   flow >= 3 <=> 删去任意一条边后，两点仍属同一边双连通分量。
// 记 cntk = #{(i<j) : flow(i,j) >= k}，则答案 = cnt1 + cnt2 + cnt3。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 3005;             // 点数上限 3000
const int MAXM = 4505;             // 边数上限 floor(3n/2) = 4500

int n, m;                          // 点数、边数
int eu[MAXM], ev[MAXM];            // 第 i 条边的两个端点（边编号 0..m-1）

// 链式前向星：每条无向边登记两次，edgeIdx 记回原始边号
int head[MAXN], nxt[2 * MAXM], to[2 * MAXM], edgeIdx[2 * MAXM], tot;

int dfn[MAXN], low[MAXN];          // Tarjan 时间戳与追溯值
int parEdge[MAXN];                 // 每个点从父亲下来的那条边号
int cur[MAXN];                     // 迭代式 DFS 的邻接边游标
char isBridge[MAXM];               // 该边是否为原图（或删边后图）的桥
int bel[MAXN];                     // 每个点的边双连通分量编号（bel 是原图的划分，供 cnt2 与挑非桥边用）
int belNow[MAXN];                  // 删边后本轮新算出的分量编号
int stk[MAXN], estk[MAXN];         // 迭代 DFS 的顶点栈与入边栈

int cls[MAXN];                     // 等价类精化过程中的当前类编号
int ord1[MAXN], ord2[MAXN];        // 计数排序用的顺序数组
int cntArr[MAXN + 2];              // 计数排序的桶

// 加边：u、v 之间连一条编号为 id 的边
void addEdge(int id, int u, int v) {
    tot++;
    to[tot] = v;
    edgeIdx[tot] = id;
    nxt[tot] = head[u];
    head[u] = tot;
}

// 求「删去第 ban 条边」后图的边双连通分量编号，写入 out[1..n]（ban < 0 表示不删边）。
// 迭代式 Tarjan 标出所有桥，再忽略桥与被删边做 flood-fill，每个连通块即一个分量。
void edgeBiconnected(int ban, int out[]) {
    for (int i = 1; i <= n; i++) {
        dfn[i] = 0;
        low[i] = 0;
        cur[i] = head[i];
        out[i] = 0;
        parEdge[i] = -1;
    }
    for (int i = 0; i < m; i++) isBridge[i] = 0;

    int timer = 0;
    for (int s = 1; s <= n; s++) {          // 图可以不连通，逐连通块 DFS
        if (dfn[s]) continue;
        int top = 0;
        dfn[s] = low[s] = ++timer;
        stk[top] = s;
        estk[top] = -1;
        top++;
        while (top > 0) {
            int u = stk[top - 1];
            if (cur[u]) {                   // 还有没走过的邻边
                int e = cur[u];
                cur[u] = nxt[e];
                int id = edgeIdx[e];
                if (id == ban) continue;    // 这条边被删掉了
                int v = to[e];
                if (!dfn[v]) {              // 树边：把 v 压栈，稍后回溯时判桥
                    dfn[v] = low[v] = ++timer;
                    parEdge[v] = id;
                    stk[top] = v;
                    estk[top] = id;
                    top++;
                } else if (id != parEdge[u] && dfn[v] < low[u]) {
                    low[u] = dfn[v];        // 回边，指向祖先
                }
            } else {                        // 回溯：u 的子树已经处理完
                top--;
                int pe = estk[top];
                if (top > 0) {
                    int p = stk[top - 1];
                    if (low[u] > dfn[p]) isBridge[pe] = 1;   // 树边 (p,u) 是桥
                    if (low[u] < low[p]) low[p] = low[u];
                }
            }
        }
    }

    int comp = 0;
    for (int s = 1; s <= n; s++) {          // 忽略桥与被删边，逐块染色
        if (out[s]) continue;
        out[s] = ++comp;
        int sp = 0;
        stk[sp++] = s;
        while (sp > 0) {
            int u = stk[--sp];
            for (int e = head[u]; e; e = nxt[e]) {
                int id = edgeIdx[e];
                if (id == ban || isBridge[id]) continue;
                int v = to[e];
                if (!out[v]) {
                    out[v] = comp;
                    stk[sp++] = v;
                }
            }
        }
    }
}

// 统计「编号相同的点对」个数：某等价关系下的点对数 C(k,2) 之和
ll countEqualPairs(int a[]) {
    static int buf[MAXN];
    for (int i = 1; i <= n; i++) buf[i - 1] = a[i];
    sort(buf, buf + n);
    ll res = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && buf[j] == buf[i]) j++;
        ll c = j - i;
        res += c * (c - 1) / 2;
        i = j;
    }
    return res;
}

// 把等价类按 (cls, belNow) 两元组重新编号：两趟计数排序，等价类只会被细分，绝不合并。
// 好处是全程确定性（不依赖哈希），且每轮代价 O(n)。
void refine(int maxCls) {
    // 第一趟：按 belNow 稳定排序（belNow ∈ [1, n]）
    for (int i = 0; i <= n + 1; i++) cntArr[i] = 0;
    for (int v = 1; v <= n; v++) cntArr[belNow[v]]++;
    int sum = 0;
    for (int i = 0; i <= n + 1; i++) {
        int c = cntArr[i];
        cntArr[i] = sum;
        sum += c;
    }
    for (int v = 1; v <= n; v++) ord1[cntArr[belNow[v]]++] = v;

    // 第二趟：在 bel 有序的基础上按 cls 稳定排序，得到 (cls, bel) 的字典序
    for (int i = 0; i <= maxCls + 1; i++) cntArr[i] = 0;
    for (int i = 0; i < n; i++) cntArr[cls[ord1[i]]]++;
    sum = 0;
    for (int i = 0; i <= maxCls + 1; i++) {
        int c = cntArr[i];
        cntArr[i] = sum;
        sum += c;
    }
    for (int i = 0; i < n; i++) ord2[cntArr[cls[ord1[i]]]++] = ord1[i];

    // 相邻两个 (cls, bel) 只要不同就开一个新类
    int r = 0;
    for (int i = 0; i < n; i++) {
        int v = ord2[i];
        if (i > 0) {
            int u = ord2[i - 1];
            if (cls[v] != cls[u] || belNow[v] != belNow[u]) r++;
        }
        cntArr[v] = r;                  // 先借用 cntArr 暂存新编号
    }
    for (int v = 1; v <= n; v++) cls[v] = cntArr[v];
}

// 并查集（路径折半），只用来数连通分量
int fa[MAXN];
int findRoot(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    tot = 0;
    for (int i = 1; i <= n; i++) head[i] = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        if (scanf("%d %d", &x, &y) != 2) return 0;
        eu[i] = x;
        ev[i] = y;
        addEdge(i, x, y);
        addEdge(i, y, x);
    }

    // ---- cnt1：连通分量 -> flow >= 1 的点对数 ----
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) {
        int a = findRoot(eu[i]);
        int b = findRoot(ev[i]);
        if (a != b) fa[a] = b;
    }
    for (int i = 1; i <= n; i++) cls[i] = findRoot(i);
    ll cnt1 = countEqualPairs(cls);

    // ---- cnt2：原图的边双连通分量 -> flow >= 2 的点对数 ----
    edgeBiconnected(-1, bel);
    ll cnt2 = countEqualPairs(bel);
    // ---- cnt3：每删一条「非桥边」做一次精化 -> flow >= 3 的点对数 ----------------
    // 删掉一条桥不会改变原图的边双划分（删边只会让划分变细、不可能合并，
    // 而桥不在任何非平凡边双块的内部），所以桥无需检验。
    for (int v = 1; v <= n; v++) cls[v] = 0;
    ll cnt3 = 0;
    if (m > 0) {
        int nonBridge = 0;
        for (int i = 0; i < m; i++)
            if (bel[eu[i]] == bel[ev[i]]) nonBridge++;   // 非桥：两端点在同一分量
        if (nonBridge > 0) {
            int maxCls = 0;
            for (int ban = 0; ban < m; ban++) {
                if (bel[eu[ban]] != bel[ev[ban]]) continue;   // 桥跳过
                edgeBiconnected(ban, belNow);
                refine(maxCls);
                maxCls = 0;
                for (int v = 1; v <= n; v++)
                    if (cls[v] > maxCls) maxCls = cls[v];
                if (maxCls == n - 1) break;   // 全是单点，再分下去 cnt3 必然是 0
            }
            cnt3 = countEqualPairs(cls);
        }
    }

    printf("%lld\n", cnt1 + cnt2 + cnt3);
    return 0;
}
