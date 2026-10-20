/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 17:50
 */
// 次短路：求 1 到 n 严格大于最短路的路径长度中的最小值。
// 题面允许路径共用道路、允许回头，所以次短路可能不是简单路径，
// 例如链 1-2-3（边权皆 1）的次短路是 1-2-1-2-3 = 4，比最短路长且走了一遍回头路。
// 因此不能在简单路径空间里枚举，而是把每个点的状态从一个距离扩成两个严格不同的距离：
//   dist1[v] 到 v 的最小值；dist2[v] 严格大于 dist1[v] 的最小值。
// 用堆按长度升序弹出候选，每条候选都是一条真实路径；一个点的最短路被推翻时，
// 旧值不能丢——它仍是真实路径，应降级为次短候选，这正是不写出那个交换就会错的地方。
// 这里不需要 visited 数组：状态扩成两个后一个点要被处理两次，定型判断从"按点"
// 变成"按记录"，用 d > dist2[u] 筛掉过期记录即可。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000 + 5;        // 点数上界 N <= 5000
const int MAXM = 100000 * 2 + 5;  // 边数上界 R <= 1e5，无向边存两次
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    // 小根堆：距离大的排后面
    bool operator<(const HeapNode& other) const {
        return dist > other.dist;
    }
};

int n, r;
int head[MAXN];   // 前向星头指针，head[u] 是 u 的第一条出边编号，0 表示没有边
int to[MAXM];     // 第 i 条边的终点
int nxt[MAXM];    // 第 i 条边在同一出发点下的下一条边
int w[MAXM];      // 第 i 条边的长度
int edge_cnt;     // 已加入的边数，同时是边编号游标
long long dist1[MAXN];  // 到 i 的最短距离
long long dist2[MAXN];  // 到 i 的次短距离，要求严格大于 dist1[i]

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
    }
}

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra() {
    for (int i = 1; i <= n; i++) {
        dist1[i] = INF;
        dist2[i] = INF;
    }

    priority_queue<HeapNode> pq;
    dist1[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        long long d = cur.dist;

        // 这条记录既不是最短路也不是次短路，早已被更优的值取代，展开它无益
        if (d > dist2[u]) continue;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            long long nd = d + w[i];

            // 找到了更短的最短路：旧的最短路是真实路径，不能丢，
            // 通过交换把它降级成次短候选（交换后 nd 就是旧的最短路值）
            if (nd < dist1[v]) {
                long long old_shortest = dist1[v];
                dist1[v] = nd;
                nd = old_shortest;
                pq.push({v, dist1[v]});
            }

            // 只接受严格大于最短路、且能改善次短的候选。
            // 长度等于最短路的另一条路径不算次短路，所以这里是 < 而不是 <=
            if (dist1[v] < nd && nd < dist2[v]) {
                dist2[v] = nd;
                pq.push({v, dist2[v]});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> r;
    init_graph();

    for (int i = 1; i <= r; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);  // 道路双向
    }

    dijkstra();

    cout << dist2[n] << '\n';
    return 0;
}
