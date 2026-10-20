/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-10-20 10:40
 */
// 最短路计数：无权图里 1 到每个点的最短路条数（答案对 100003 取模）。
// 无权图的最短路就是 BFS 层数，所以只需一次 BFS：
// 首次访问确定 dist[v]，同时把 ways[u] 抄给 ways[v]；
// 遇到 dist[v] == dist[u] + 1 的边，说明 v 多了一条来自 u 的最短路，累加 ways[u]。
// 重边和自环都不需要特判：重边是两条独立的边，BFS 会分别遍历，正好分别计数。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;    // 点数上界
const int MAXM = 2000005;    // 边数上界
const int MOD = 100003;      // 题面要求的取模数

int n, m;
int head[MAXN];              // 前向星头指针，head[u] 是 u 的第一条出边编号，0 表示没有边
int to[MAXM * 2];            // 第 i 条边的终点；无向图每条边存两次，所以开两倍
int nxt[MAXM * 2];           // 第 i 条边的同一起点的下一条边
int edge_cnt;                // 已加入的边数，同时是边编号游标
int dist_node[MAXN];         // 1 到 i 的最短距离（BFS 层数），-1 表示还没访问到
int ways[MAXN];              // 1 到 i 的最短路条数（已对 MOD 取模）

// 加一条有向边 u -> v，挂到 u 的链表头部
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        // 无向边存成两个方向；同一对点重复输入就是重边，保留两条各自计数
        add_edge(u, v);
        add_edge(v, u);
    }
}

// 一次 BFS 同时求出最短距离和最短路条数
void bfs() {
    for (int i = 1; i <= n; i++) {
        dist_node[i] = -1;
        ways[i] = 0;
    }

    queue<int> que;
    dist_node[1] = 0;        // 起点到自己是距离 0 的一条路径
    ways[1] = 1;
    que.push(1);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (dist_node[v] == -1) {
                // 第一次访问到 v，BFS 保证这是最短路；到 u 的每条最短路都能延长一步到达 v
                dist_node[v] = dist_node[u] + 1;
                ways[v] = ways[u];
                que.push(v);
            } else if (dist_node[v] == dist_node[u] + 1) {
                // v 已经在更浅或同层被访问过。只有「正好深一层」的边才是最短路边
                ways[v] += ways[u];
                if (ways[v] >= MOD) {
                    ways[v] %= MOD;
                }
            }
            // 其余情况 dist_node[v] <= dist_node[u]：这条边不在最短路树上，直接跳过
        }
    }
}

void solve() {
    bfs();
    for (int i = 1; i <= n; i++) {
        cout << ways[i] % MOD << '\n';  // 不可达的点 ways 始终是 0，正好符合题意
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
