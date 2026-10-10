/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 19:06
 * update_at: 2026-10-07 19:06
 */
// ROJ 1729《魔法石》
// 题意：n 个岛、m 条无向石桥（走过即崩塌，每条边至多走一次），c=1 表示桥心有魔法石。
//       问是否存在一条 src → dst 的「边不重复的走法(trail)」，途中经过至少一条 c=1 的边。
// 等价原题：Codeforces 652E Pursuit For Artifacts（人物 Johnny、边权 0/1、多组数据）。
//
// 判定准则：tarjan 求割边 → 非割边连通块缩成边双(e-DCC) → 得到「桥树」；
//   设 P 为桥树上 comp[src] → comp[dst] 的唯一路径（不可达即 NO），则
//   答案 = YES ⇔ P 上存在权 1 的桥，或 P 上某个边双内部存在权 1 的边。
//   理由：边双是 2-边连通的，任意两条边落在同一条闭 trail 上（把入口→出口连一条虚边后
//   用「闭 trail 内任意两条边可用耳朵分解拼起来」的结论），所以边双内部可以顺路取石；
//   而割边必须沿 P 的方向各走一次，绕到 P 之外的分支就再也回不来（那条边是桥）。
//
// 实现要点：n,m ≤ 3e5 且 T ≤ 10，长链会爆递归栈 → tarjan 写成显式栈的迭代版；
//   Σm 可达 3e6 → 手写 fread 快读 + 输出缓冲；割边按「边下标」跳过父边（eid^1），
//   重边与自环都不会被误判；每组 O(n+m)，全局数组按下标覆盖复用。
//
// 数据说明：素材源自带 data.py 生成脚本，data/ 是自造的（按 CF652E 的保证：无自环、
//   无重边、每组图连通），题面亦为网络重建，与官方原题细节可能略有出入。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300005;   // 岛数上限
const int MAXM = 300005;   // 桥数上限

int n, m;                  // 本组数据的岛数、桥数

// 链式前向星存原图，边成对加入，eid^1 是反向边
int head[MAXN];
int eto[2 * MAXM];
int enxt[2 * MAXM];
int ewt[2 * MAXM];
int ecnt;

int dfn[MAXN];             // tarjan 时间戳
int low[MAXN];
int itE[MAXN];             // 迭代 DFS 中当前扫到的出边
int parE[MAXN];            // 结点在 DFS 树中的入边下标
bool isBr[2 * MAXM];       // 该有向边是否为割边的某一侧

int fa[MAXN];              // 并查集：把非割边连成的边双缩点
int sz[MAXN];
int comp[MAXN];            // 结点所属边双的根
bool hasArt[MAXN];         // 边双内部是否存在权 1 的边

// 桥树的链式前向星
int thead[MAXN];
int tto[2 * MAXM];
int tnxt[2 * MAXM];
int twt[2 * MAXM];
int tcnt;

int stk[MAXN];             // 迭代 tarjan 的栈
int que[MAXN];             // 桥树上 BFS 的队列
bool vis[MAXN];
bool acc[MAXN];            // 桥树上从 comp[src] 一路走来的「是否已能取到石」前缀或

char inBuf[1 << 22];       // 输入缓冲（每组最多 3e5 行，用 fread 比 cin 稳）
int inLen = 0, inPos = 0;

char outBuf[1 << 16];      // 输出缓冲
int outPos = 0;

// ---------- 快读 / 快写 ----------
int readInt() {
    if (inPos == inLen) {
        inLen = (int)fread(inBuf, 1, sizeof(inBuf), stdin);
        inPos = 0;
        if (inLen == 0) return -1;
    }
    while (inPos < inLen && (inBuf[inPos] < '0' || inBuf[inPos] > '9')) {
        if (++inPos == inLen) {
            inLen = (int)fread(inBuf, 1, sizeof(inBuf), stdin);
            inPos = 0;
            if (inLen == 0) return -1;
        }
    }
    int x = 0;
    while (inPos < inLen && inBuf[inPos] >= '0' && inBuf[inPos] <= '9') {
        x = x * 10 + (inBuf[inPos] - '0');
        if (++inPos == inLen) {
            inLen = (int)fread(inBuf, 1, sizeof(inBuf), stdin);
            inPos = 0;
            if (inLen == 0) break;
        }
    }
    return x;
}

void outStr(const char *s, int len) {
    if (outPos + len > (int)sizeof(outBuf)) {
        fwrite(outBuf, 1, outPos, stdout);
        outPos = 0;
    }
    for (int i = 0; i < len; ++i) outBuf[outPos++] = s[i];
}

void addEdge(int u, int v, int w) {
    eto[ecnt] = v; ewt[ecnt] = w; enxt[ecnt] = head[u]; head[u] = ecnt++;
}

void addTreeEdge(int u, int v, int w) {
    tto[tcnt] = v; twt[tcnt] = w; tnxt[tcnt] = thead[u]; thead[u] = tcnt++;
}

int findRoot(int x) {
    int r = x;
    while (fa[r] != r) r = fa[r];
    while (fa[x] != r) {           // 路径压缩
        int nx = fa[x];
        fa[x] = r;
        x = nx;
    }
    return r;
}

void unite(int a, int b) {
    a = findRoot(a); b = findRoot(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);  // 按大小合并
    fa[b] = a; sz[a] += sz[b];
}

void solve() {
    int T = readInt();
    if (T < 0) T = 0;
    while (T--) {
        n = readInt(); m = readInt();
        if (n < 1) n = 1;
        if (m < 0) m = 0;

        // 只清本次用到的范围，避免 T 组间反复 O(MAXN) 清空
        for (int i = 1; i <= n; ++i) {
            head[i] = -1;
            thead[i] = -1;
            dfn[i] = 0;
            parE[i] = -1;
            fa[i] = i;
            sz[i] = 1;
            hasArt[i] = false;
            vis[i] = false;
            acc[i] = false;
        }
        ecnt = 0; tcnt = 0;

        for (int i = 0; i < m; ++i) {
            int x = readInt(), y = readInt(), c = readInt();
            addEdge(x, y, c);
            addEdge(y, x, c);
        }
        for (int i = 0; i < ecnt; ++i) isBr[i] = false;

        // ---------- 迭代式 tarjan 求割边（按边下标跳过父边，重边/自环安全） ----------
        int timer = 0;
        for (int root = 1; root <= n; ++root) {
            if (dfn[root]) continue;
            int top = 0;
            stk[top++] = root;
            dfn[root] = low[root] = ++timer;
            itE[root] = head[root];
            parE[root] = -1;
            while (top > 0) {
                int u = stk[top - 1];
                int e = itE[u];
                if (e != -1) {
                    itE[u] = enxt[e];
                    if (parE[u] != -1 && e == (parE[u] ^ 1)) continue;  // 不走父边的反向边
                    int v = eto[e];
                    if (!dfn[v]) {                 // 树边，压栈继续深搜
                        parE[v] = e;
                        itE[v] = head[v];
                        dfn[v] = low[v] = ++timer;
                        stk[top++] = v;
                    } else if (dfn[v] < low[u]) {  // 返祖边，用 dfn 更新 low
                        low[u] = dfn[v];
                    }
                } else {
                    --top;                          // u 出栈，把 low 回传给父亲
                    int pe = parE[u];
                    if (pe != -1) {
                        int p = eto[pe ^ 1];
                        if (low[u] < low[p]) low[p] = low[u];
                        if (low[u] > dfn[p]) {      // (p,u) 是割边
                            isBr[pe] = true;
                            isBr[pe ^ 1] = true;
                        }
                    }
                }
            }
        }

        // ---------- 非割边连通块 = 边双，并查集缩点 ----------
        for (int e = 0; e < ecnt; e += 2) {
            if (!isBr[e]) unite(eto[e], eto[e ^ 1]);
        }
        for (int v = 1; v <= n; ++v) comp[v] = findRoot(v);

        for (int e = 0; e < ecnt; e += 2) {
            if (!isBr[e]) {
                if (ewt[e]) hasArt[comp[eto[e]]] = true;   // 边双内部的魔法石
            } else {
                addTreeEdge(comp[eto[e]], comp[eto[e ^ 1]], ewt[e]);  // 桥 = 桥树的边
                addTreeEdge(comp[eto[e ^ 1]], comp[eto[e]], ewt[e]);
            }
        }

        int src = readInt(), dst = readInt();
        int cs = comp[src], cd = comp[dst];

        // ---------- 桥树上从 comp[src] 广搜，累积「路上能否取到石」 ----------
        int qh = 0, qt = 0;
        que[qt++] = cs;
        vis[cs] = true;
        acc[cs] = hasArt[cs];
        while (qh < qt) {
            int u = que[qh++];
            for (int e = thead[u]; e != -1; e = tnxt[e]) {
                int v = tto[e];
                if (vis[v]) continue;
                vis[v] = true;
                acc[v] = acc[u] || twt[e] || hasArt[v];  // 前缀或：桥权 1 或边双内部有石
                que[qt++] = v;
            }
        }

        // cs == cd 时 acc[cd] 就是「该边双内部是否有石」，同样成立
        if (vis[cd] && acc[cd]) outStr("YES\n", 4);
        else outStr("NO\n", 3);
    }
    if (outPos) fwrite(outBuf, 1, outPos, stdout);
}

int main() {
    solve();
    return 0;
}
