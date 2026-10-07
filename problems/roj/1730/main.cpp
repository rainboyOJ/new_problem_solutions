/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 19:03
 * update_at: 2026-10-07 19:03
 */
// 一本通 1730《二分图》：判定每条边是否属于某个「饱和左部」的匹配（题面保证 n <= m）。
//   1. Hopcroft-Karp 求最大匹配；若匹配数不足 n，则不存在大小为 n 的匹配，全部输出 1。
//   2. 取定一个最大匹配 M，按 M 建交错有向图 D（左部点 1..n，右部点 n+1..n+m）：
//        匹配边 u-v 建成弧 u -> v，非匹配边 u-v 建成弧 v -> u。
//   3. 非匹配边 (u,v) 属于某个大小为 n 的匹配，当且仅当
//        (a) u 与 v 在 D 的同一个强连通分量里（该边落在一条交错环上），或
//        (b) v 能从某个「M 未匹配的右部点」沿 D 走到（该边落在一条交错路上，翻转前缀即可）。
//      匹配边本身恒属于。
//   4. 输出取反：属于输出 0，否则（含非边）输出 1。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 305;    // 左部点数上限
const int MAXM = 1505;   // 右部点数上限
const int MAXV = MAXN + MAXM;
const int MAXE = 460005; // 有向弧上限：n * m = 300 * 1500 = 450000
const int INF = 0x3f3f3f3f;

int n, m;                 // 左部 n 个点、右部 m 个点（保证 n <= m）
vector<int> g[MAXN];      // g[u] = 左部点 u 的全部右部邻居
int matchL[MAXN];         // matchL[u] = 左部点 u 匹配到的右部点，0 表示未匹配
int matchR[MAXM];         // matchR[v] = 右部点 v 匹配到的左部点，0 表示未匹配
int distL[MAXN];          // 分层 BFS 中左部点 u 的层号，INF 表示本轮不可达

// 链式前向星存交错有向图 D
int head[MAXV];           // head[x] = 顶点 x 的第一条出弧编号
struct Edge {
    int to;               // 弧的终点
    int ne;               // 同起点的下一条弧
};
Edge ed[MAXE];
int edge_cnt;

int dfn[MAXV], low[MAXV]; // Tarjan 的时间戳与回溯值
int stk[MAXV], stk_top;   // Tarjan 的栈
bool in_stk[MAXV];        // 顶点是否还在栈中
int scc_id[MAXV], scc_cnt; // 每个顶点所属的强连通分量编号
int timer;

bool reachable[MAXV];     // 从「M 未匹配的右部点」出发在 D 上可达
char ans[MAXN][MAXM];     // 答案矩阵：1 表示该边不属于任何大小为 n 的匹配
char line[MAXM];          // 读入一行的缓冲

// 往交错有向图 D 里加一条弧 u -> v
void add_edge(int u, int v) {
    edge_cnt++;
    ed[edge_cnt].to = v;
    ed[edge_cnt].ne = head[u];
    head[u] = edge_cnt;
}

// Hopcroft-Karp 的分层：未匹配的左部点为第 0 层，返回本轮是否存在增广路
bool hk_bfs() {
    queue<int> que;
    for (int u = 1; u <= n; u++) {
        if (matchL[u] == 0) {
            distL[u] = 0;
            que.push(u);
        } else {
            distL[u] = INF;
        }
    }
    bool found = false;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : g[u]) {
            int w = matchR[v];
            if (w == 0) {
                found = true;               // 存在一条长度更短或同长的增广路
            } else if (distL[w] == INF) {
                distL[w] = distL[u] + 1;    // 沿匹配边继续分层
                que.push(w);
            }
        }
    }
    return found;
}

// 沿分层图找一条增广路并翻转匹配
bool hk_dfs(int u) {
    for (int v : g[u]) {
        int w = matchR[v];
        if (w == 0 || (distL[w] == distL[u] + 1 && hk_dfs(w))) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    distL[u] = INF;                         // 本轮 u 已确认失败，避免重复搜索
    return false;
}

// 返回最大匹配的边数
int hopcroft_karp() {
    int cnt = 0;
    while (hk_bfs()) {
        for (int u = 1; u <= n; u++) {
            if (matchL[u] == 0 && hk_dfs(u)) cnt++;
        }
    }
    return cnt;
}

// Tarjan 求强连通分量（D 的顶点数不超过 1800，递归深度安全）
void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk[++stk_top] = u;
    in_stk[u] = true;
    for (int e = head[u]; e; e = ed[e].ne) {
        int v = ed[e].to;
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        scc_cnt++;
        int w;
        do {
            w = stk[stk_top--];
            in_stk[w] = false;
            scc_id[w] = scc_cnt;
        } while (w != u);
    }
}

// 从所有「M 未匹配的右部点」出发做 BFS，标出 D 上能到达的顶点
void bfs_from_free_right() {
    queue<int> que;
    for (int v = 1; v <= m; v++) {
        if (matchR[v] == 0) {
            reachable[n + v] = true;
            que.push(n + v);
        }
    }
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (int e = head[x]; e; e = ed[e].ne) {
            int y = ed[e].to;
            if (!reachable[y]) {
                reachable[y] = true;
                que.push(y);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", line + 1);
        for (int j = 1; j <= m; j++) {
            if (line[j] == '1') g[i].push_back(j);
        }
    }
    int matched = hopcroft_karp();
    // 默认全部输出 1：非边，以及不属于任何大小为 n 的匹配的边
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) ans[i][j] = '1';
        ans[i][m + 1] = '\0';
    }
    if (matched < n) {
        for (int i = 1; i <= n; i++) puts(ans[i] + 1);
        return 0;
    }
    // 按匹配 M 建交错有向图 D
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (matchL[u] == v) add_edge(u, n + v); // 匹配边：左 -> 右
            else add_edge(n + v, u);                // 非匹配边：右 -> 左
        }
    }
    for (int x = 1; x <= n + m; x++) {
        if (dfn[x] == 0) tarjan(x);
    }
    bfs_from_free_right();
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (matchL[u] == v) ans[u][v] = '0';                 // 匹配边恒属于
            else if (scc_id[u] == scc_id[n + v]) ans[u][v] = '0'; // 条件 (a)：交错环
            else if (reachable[n + v]) ans[u][v] = '0';           // 条件 (b)：交错路
        }
    }
    for (int i = 1; i <= n; i++) puts(ans[i] + 1);
    return 0;
}
