/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 07:05
 * update_at: 2026-10-06 11:13
 */
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 55;

int n;                          // 终点编号为 n，起点编号为 0，总点数 n+1
vector<int> g[MAXN];            // g[u] = 从 u 引出的单行道终点列表
bool vis[MAXN];                 // BFS 访问标记
bool unavoidable[MAXN];         // unavoidable[v] = v 是否为必经点
bool splitting[MAXN];           // splitting[v] = v 是否为中间路口（分割点）

// 从 start 出发、不经过 blocked 点的 BFS，返回 N 是否可达；
// 同时把访问到的点记在 mark[] 里（mark 为 NULL 时只判可达）
bool bfs_reach(int start, int blocked, bool *mark) {
    bool inq[MAXN] = { false };
    queue<int> q;
    q.push(start);
    inq[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (mark != NULL) mark[u] = true;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i];
            if (v == blocked || inq[v]) continue; // 删点即禁止经过 blocked
            inq[v] = true;
            q.push(v);
        }
    }
    return inq[n];
}

// 判断 a、b 两个点集是否相交（点集用 bool 数组表示）
bool has_intersection(bool *a, bool *b) {
    for (int i = 0; i <= n; ++i)
        if (a[i] && b[i]) return true;
    return false;
}

int main() {
    // 读入：每行是以 -2 结尾的街道列表，最后一行只有 -1
    int from = 0;
    while (true) {
        int x;
        scanf("%d", &x);
        if (x == -1) break;
        if (x == -2) { ++from; continue; }
        g[from].push_back(x);
    }
    n = from - 1; // from 最后停在终点所在行号，即 N

    // 第一问：删去 v 后 0 无法到达 n，则 v 是不可避免的路口
    for (int v = 1; v < n; ++v)
        if (!bfs_reach(0, v, NULL)) unavoidable[v] = true;

    // 第二问：v 是必经点，且 0 避开 v 的可达集与 v 的可达集不相交
    bool reach0[MAXN], reachS[MAXN];
    for (int v = 1; v < n; ++v) {
        if (!unavoidable[v]) continue;
        for (int i = 0; i <= n; ++i) { reach0[i] = false; reachS[i] = false; }
        bfs_reach(0, v, reach0); // 前半段：从 0 出发不经过 v 能到的点
        bfs_reach(v, -1, reachS); // 后半段：从 v 出发无限制能到的点
        // 两集合除 v 外无公共点（v 不在 reach0 中），即唯一公共点是 v
        if (!has_intersection(reach0, reachS)) splitting[v] = true;
    }

    // 输出两行：先数量，再按升序的点编号
    int cnt = 0;
    for (int v = 1; v < n; ++v) if (unavoidable[v]) ++cnt;
    printf("%d", cnt);
    for (int v = 1; v < n; ++v) if (unavoidable[v]) { printf(" %d", v); }
    printf("\n");

    cnt = 0;
    for (int v = 1; v < n; ++v) if (splitting[v]) ++cnt;
    printf("%d", cnt);
    for (int v = 1; v < n; ++v) if (splitting[v]) { printf(" %d", v); }
    printf("\n");
    return 0;
}
