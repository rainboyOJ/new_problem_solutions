/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:30
 * update_at: 2026-10-10 13:30
 */

// 雨天的尾巴：树上差分 + 动态开点权值线段树合并求路径众数。
// 路径 (x,y) 拆成 x+1、y+1、lca-1、lca父-1 四个差分点，
// 逆 BFS 序把子树线段树并到父亲，每个点取众数（并列取编号最小的种类）。
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXLOG = 19;                 // 2^17 > 100000
const int MAXNODE = 7200010;           // 4m 次插入，每次最多 ceil(log2 K)+1 = 18 个点

int n, m, K;
int parent[MAXN];
int depth[MAXN];
int ordArr[MAXN];
int up[MAXLOG][MAXN];
int roots[MAXN];
int ansArr[MAXN];
int qx[MAXN], qy[MAXN], qz[MAXN];
vector<int> adj[MAXN];
vector<int> kinds; // 离散化后的物品种类（升序）

// 动态开点权值线段树的静态池，0 号点是空树哨兵
int lc[MAXNODE];
int rc[MAXNODE];
int mxc[MAXNODE];
int nodeCnt = 1; // 0 号留空

int newNode() {
    int id = nodeCnt++;
    return id; // 池已清零
}

void pull(int node) { // 由左右孩子重算 node 的最大单类计数
    if (mxc[lc[node]] >= mxc[rc[node]]) mxc[node] = mxc[lc[node]];
    else mxc[node] = mxc[rc[node]];
}

int insertNode(int root, int pos, int delta) { // 给叶子 pos 加 delta
    if (root == 0) root = newNode();
    int cur = root, l = 0, r = K - 1;
    int path[MAXLOG + 2], pc = 0; // 自顶向下记录路径，最后统一回推
    path[pc++] = cur;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            int nxt = lc[cur];
            if (nxt == 0) { nxt = newNode(); lc[cur] = nxt; }
            r = mid;
            cur = nxt;
        } else {
            int nxt = rc[cur];
            if (nxt == 0) { nxt = newNode(); rc[cur] = nxt; }
            l = mid + 1;
            cur = nxt;
        }
        path[pc++] = cur;
    }
    mxc[cur] += delta; // 到达叶子：叶子上的计数本身就是它的 mx
    for (int i = pc - 2; i >= 0; --i) pull(path[i]);
    return root;
}

int mergeTree(int a, int b) { // 把 b 破坏式并入 a，返回新根
    if (a == 0 || b == 0) return a | b;
    if (lc[a] == 0 && rc[a] == 0) { // a 是叶子，b 同区间也必是叶子
        mxc[a] += mxc[b];
        return a;
    }
    lc[a] = mergeTree(lc[a], lc[b]);
    rc[a] = mergeTree(rc[a], rc[b]);
    pull(a);
    return a;
}

int queryMode(int root) { // 众数种类；空树返回 0（并列取左 = 编号更小的种类）
    if (root == 0 || mxc[root] == 0) return 0;
    int cur = root, l = 0, r = K - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (mxc[lc[cur]] >= mxc[rc[cur]]) { cur = lc[cur]; r = mid; }
        else { cur = rc[cur]; l = mid + 1; }
    }
    return kinds[l];
}

int lca(int u, int v, int rows) {
    if (depth[u] < depth[v]) { int t = u; u = v; v = t; }
    int diff = depth[u] - depth[v];
    for (int k = 0; k < rows; ++k) {
        if (diff >> k & 1) u = up[k][u];
    }
    if (u == v) return u;
    for (int k = rows - 1; k >= 0; --k) {
        if (up[k][u] != up[k][v]) { u = up[k][u]; v = up[k][v]; }
    }
    return up[0][u];
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0; // 空输入安全返回
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // 从 1 号点 BFS（order 边遍历边增长，等价于队列）
    for (int i = 0; i <= n; ++i) parent[i] = 0;
    int ordCnt = 0;
    ordArr[ordCnt++] = 1;
    for (int i = 0; i < ordCnt; ++i) {
        int u = ordArr[i];
        for (int j = 0; j < (int)adj[u].size(); ++j) {
            int v = adj[u][j];
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                ordArr[ordCnt++] = v;
            }
        }
    }

    // 倍增表：up[k][v] 是 v 向上跳 2^k 步到的祖先，0 号点是哨兵
    int bitlen = 0;
    while ((1 << bitlen) <= n - 1) ++bitlen; // (n-1).bit_length()
    int rows = 1 + (bitlen > 1 ? bitlen : 1);
    if (rows > MAXLOG) rows = MAXLOG;
    for (int x = 0; x <= n; ++x) up[0][x] = parent[x];
    for (int k = 1; k < rows; ++k) {
        for (int x = 0; x <= n; ++x) up[k][x] = up[k - 1][up[k - 1][x]];
    }

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &qx[i], &qy[i], &qz[i]);
        kinds.push_back(qz[i]);
    }
    sort(kinds.begin(), kinds.end());
    kinds.erase(unique(kinds.begin(), kinds.end()), kinds.end());

    // 叶子数 K 必须同时 >= 种类数（装下差分点）和 n-1 的位长
    K = kinds.size();
    if (bitlen > K) K = bitlen;
    if (K == 0) K = 1;

    for (int i = 0; i < m; ++i) {
        int x = qx[i], y = qy[i];
        int kind = lower_bound(kinds.begin(), kinds.end(), qz[i]) - kinds.begin();
        int l = lca(x, y, rows);
        roots[x] = insertNode(roots[x], kind, 1);
        roots[y] = insertNode(roots[y], kind, 1);
        roots[l] = insertNode(roots[l], kind, -1);
        if (parent[l]) roots[parent[l]] = insertNode(roots[parent[l]], kind, -1);
    }

    // 逆 BFS 序：u 的树已含全部子树差分时先取答案，再并入父节点
    for (int i = n - 1; i >= 0; --i) {
        int u = ordArr[i];
        ansArr[u] = queryMode(roots[u]);
        if (parent[u]) roots[parent[u]] = mergeTree(roots[parent[u]], roots[u]);
    }

    for (int i = 1; i <= n; ++i) printf("%d\n", ansArr[i]);
    return 0;
}
