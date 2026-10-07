/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:47
 * update_at: 2026-10-07 17:47
 */

// 1708 无限链计数
// 一条双无限链（左右都能平移，平移后视为同一条）就是禁止串 AC 自动机上的
// 一条双无限转移路径；把非终止结点、非终止转移缩成 SCC 之后，路径的 SCC
// 序列在缩点 DAG 上单调，所以每条链恰好对应「环 SCC 出发 + DAG 有限路径 +
// 环 SCC 收尾」这样一条 DAG 路径：
//   * SCC 内部边数 > 结点数 ⟺ 这个 SCC 不是简单环 ⟺ 链有无穷多条（-1）；
//   * DAG 路径上夹在中间的环 SCC 还能随便绕圈，所以路径上环 SCC 数 ≥ 3 时
//     也有无穷多条（-1）；
//   * 否则答案就是「环 SCC 到环 SCC」的 DAG 路径条数。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 10005;  // 禁止串总长 ≤ 1000 × 10 = 10000，结点数 ≤ 10001
const int MAXE = 60005;     // 每个非终止结点至多 t ≤ 6 条非终止转移

int t, n;                   // t：字母表大小；n：禁止串个数
int trie[MAXNODE][6];       // AC 自动机的完整转移（fail 指针补齐之后）
int failLink[MAXNODE];      // 失配指针
bool terminal[MAXNODE];     // 该结点或它的某个 fail 祖先是禁止串的结尾
int nodeCnt;                // 结点个数，根固定为 0

// 一张图的链式前向星：g1 是「非终止结点 + 非终止转移」的原图，
// g2 是缩点后的 DAG（保留重边，重边代表不同的转移，必须分别计数）
struct Edge {
    int to;
    int next;
};
Edge g1[MAXE];
Edge g2[MAXE];
int head1[MAXNODE], head2[MAXNODE];
int cnt1, cnt2;

void add_edge1(int u, int v) {
    cnt1++;
    g1[cnt1].to = v;
    g1[cnt1].next = head1[u];
    head1[u] = cnt1;
}

void add_edge2(int u, int v) {
    cnt2++;
    g2[cnt2].to = v;
    g2[cnt2].next = head2[u];
    head2[u] = cnt2;
}

// 把一个禁止串插入 Trie
void insert_word(const char *s) {
    int u = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (trie[u][c] == 0) trie[u][c] = ++nodeCnt;
        u = trie[u][c];
    }
    terminal[u] = true;
}

// 建 fail 指针，同时把转移补齐成「走到哪个状态」的完整转移表，
// 并把禁止标记沿 fail 链传递到每个结点
void build_fail() {
    queue<int> que;
    for (int c = 0; c < t; c++)
        if (trie[0][c]) que.push(trie[0][c]);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        terminal[u] = terminal[u] || terminal[failLink[u]];  // fail 链传递
        for (int c = 0; c < t; c++) {
            if (trie[u][c]) {
                failLink[trie[u][c]] = trie[failLink[u]][c];
                que.push(trie[u][c]);
            } else {
                trie[u][c] = trie[failLink[u]][c];
            }
        }
    }
}

int dfn[MAXNODE], low[MAXNODE], timerClock;
int stk[MAXNODE], top;
bool inStack[MAXNODE];
int sccId[MAXNODE], sccCnt;
int sccNode[MAXNODE];      // 每个 SCC 的结点数
int sccInner[MAXNODE];     // 每个 SCC 的内部边数
bool isCycleScc[MAXNODE];  // 内部边数 == 结点数 ⟺ 这个 SCC 就是一个简单环

// Tarjan 求强连通分量（只跑原图上非终止的结点）
void tarjan(int u) {
    dfn[u] = low[u] = ++timerClock;
    stk[++top] = u;
    inStack[u] = true;
    for (int e = head1[u]; e; e = g1[e].next) {
        int v = g1[e].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        sccCnt++;
        int k;
        do {
            k = stk[top--];
            inStack[k] = false;
            sccId[k] = sccCnt;
            sccNode[sccCnt]++;
        } while (k != u);
    }
}

int indeg[MAXNODE];  // 缩点 DAG 上每个 SCC 的入度，用来做 Kahn 拓扑排序
ll pathCnt[MAXNODE]; // pathCnt[v]：从某个环 SCC 出发、终点是 v 的 DAG 路径条数
int cycleOnPath[MAXNODE]; // cycleOnPath[v]：这些路径上环 SCC 个数的最大值

int main() {
    scanf("%d %d", &t, &n);
    char s[15];
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        insert_word(s);
    }
    build_fail();

    // 建原图：结点和转移都不能碰到禁止串
    for (int u = 0; u <= nodeCnt; u++) {
        if (terminal[u]) continue;
        for (int c = 0; c < t; c++) {
            int v = trie[u][c];
            if (terminal[v]) continue;
            add_edge1(u, v);
        }
    }
    for (int u = 0; u <= nodeCnt; u++)
        if (!terminal[u] && !dfn[u]) tarjan(u);

    // 缩点：统计 SCC 内部边数，跨 SCC 的边建成 DAG
    for (int u = 0; u <= nodeCnt; u++) {
        if (terminal[u]) continue;
        for (int e = head1[u]; e; e = g1[e].next) {
            int v = g1[e].to;
            if (sccId[u] == sccId[v]) {
                sccInner[sccId[u]]++;
            } else {
                add_edge2(sccId[u], sccId[v]);
                indeg[sccId[v]]++;
            }
        }
    }
    for (int i = 1; i <= sccCnt; i++) {
        if (sccInner[i] > sccNode[i]) {  // 不是简单环：同一个 SCC 里就有无穷多条链
            printf("-1\n");
            return 0;
        }
        if (sccInner[i] == sccNode[i]) isCycleScc[i] = true;
    }

    // 缩点 DAG 上按拓扑序做路径计数
    queue<int> que;
    for (int i = 1; i <= sccCnt; i++) {
        if (indeg[i] == 0) {
            que.push(i);
            cycleOnPath[i] = isCycleScc[i] ? 1 : 0;  // 路径可以就从自己这个环开始
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (cycleOnPath[u] >= 3) {  // 中间的环 SCC 可以绕任意圈：无穷多
            printf("-1\n");
            return 0;
        }
        if (isCycleScc[u]) pathCnt[u]++;  // 长度 0 的路径：自己就是一个环
        for (int e = head2[u]; e; e = g2[e].next) {
            int v = g2[e].to;
            pathCnt[v] += pathCnt[u];
            cycleOnPath[v] = max(cycleOnPath[v], cycleOnPath[u] + (isCycleScc[v] ? 1 : 0));
            if (--indeg[v] == 0) que.push(v);
        }
    }

    ll answer = 0;
    for (int i = 1; i <= sccCnt; i++)
        if (isCycleScc[i]) answer += pathCnt[i];  // 每条链以收尾的环 SCC 归类，不重不漏
    printf("%lld\n", answer);
    return 0;
}
