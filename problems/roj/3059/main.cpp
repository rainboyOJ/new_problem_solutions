/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:03
 * update_at: 2026-10-06 17:03
 */
// 可达性统计：DAG 上按拓扑逆序做位集合 DP，
// reach[v] 的第 u 位为 1 表示 v 能到达 u，合并后继用按位或。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 30005; // 点数上限
const int MAXM = 30005; // 边数上限

int n, m;
int head[MAXN];          // 链式前向星：head[v] 是 v 的第一条出边编号
int nxt[MAXM];           // 同起点下一条边
int to_[MAXM];           // 边的终点（避开 std 的 to）
int indeg[MAXN];         // 入度，用于 Kahn 拓扑排序
int topo[MAXN];          // topo[i] = 拓扑序第 i 个点
int cnt_topo = 0;        // 拓扑序长度（去重后应等于 n）
ll ans[MAXN];            // ans[v] = v 能到达的点数，最后按点编号输出

pair<int, int> edges[MAXM]; // 原始边，先排序去重再建图

bitset<MAXN> reach[MAXN]; // reach[v]：v 能到达的点集，第 u 位为 1 表示可达

// 加一条有向边 u -> v
void add_edge(int u, int v) {
    static int tot = 0;
    ++tot;
    to_[tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        edges[i] = make_pair(x, y);
    }

    // 题面允许重复边：先排序去重，否则入度虚高，拓扑排序会漏点
    sort(edges + 1, edges + m + 1);
    int m2 = unique(edges + 1, edges + m + 1) - (edges + 1);
    for (int i = 1; i <= m2; ++i) {
        add_edge(edges[i].first, edges[i].second);
        ++indeg[edges[i].second];
    }

    // Kahn 算法求拓扑序：入度为 0 的点先入队
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++cnt_topo;
        topo[cnt_topo] = u;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to_[e];
            --indeg[v];
            if (indeg[v] == 0) q.push(v);
        }
    }

    // 拓扑逆序递推：轮到 v 时它的所有后继都已算完
    // R(v) = {v} ∪ R(w1) ∪ R(w2) ∪ ...
    for (int i = cnt_topo; i >= 1; --i) {
        int v = topo[i];
        reach[v][v] = 1; // 自己到自己也算可达
        for (int e = head[v]; e; e = nxt[e])
            reach[v] |= reach[to_[e]];
        ans[v] = (ll)reach[v].count(); // 数二进制里 1 的个数
    }

    // 输出按点编号 1..n 的顺序
    for (int v = 1; v <= n; ++v)
        printf("%lld\n", ans[v]);
    return 0;
}
