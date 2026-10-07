/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 07:33
 * update_at: 2026-10-08 07:33
 */
// main.cpp：有向图的可达性查询，对每个起点各跑一次 BFS 预处理出全源可达矩阵，
// 之后每次询问 O(1) 查表。与 main.py 同一算法。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // 点数上限 10^3（题面 1 <= N, M <= 10^3），留一点余量
const int MAXM = 1005; // 边数上限同上

int n, m, k; // 点数、边数、询问数

struct Edge { // 链式前向星的一条出边：指向 to，同起点的下一条边编号是 nxt
    int to;
    int nxt;
};
Edge edge[MAXM];
int head[MAXN]; // head[u] = u 的第一条出边编号，0 表示没有出边
int ecnt;       // 已存边数

char reach[MAXN][MAXN]; // reach[s][v]：从 s 出发能否抵达 v；只有 0/1，用 char 省内存
int que[MAXN];          // 手写 BFS 队列，每个点在每个起点下最多入队一次，容量 N 足够

// 加入一条有向边 u -> v（只存 u 到 v 这一个方向）
void add_edge(int u, int v) {
    ++ecnt;
    edge[ecnt].to = v;
    edge[ecnt].nxt = head[u];
    head[u] = ecnt;
}

// 从起点 s 出发 BFS，把 s 能抵达的点全部标记进 reach[s][*]
void bfs_from(int s) {
    int qh = 0, qt = 0;
    reach[s][s] = 1; // 路径长度可以为 0，任何点都能抵达自己
    que[qt++] = s;   // 入队即标记，避免同一个点被重复入队
    while (qh < qt) {
        int u = que[qh++];
        for (int e = head[u]; e; e = edge[e].nxt) {
            int v = edge[e].to;
            if (!reach[s][v]) {
                reach[s][v] = 1;
                que[qt++] = v;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v); // 有向图，不要加成双向边
    }

    // 每个起点单独跑一次 BFS：不能因为 reach[s][s] 被别的起点标过就跳过起点 s
    for (int s = 1; s <= n; s++) {
        bfs_from(s);
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        cout << (reach[x][y] ? "Yes" : "No") << "\n";
    }

    return 0;
}
