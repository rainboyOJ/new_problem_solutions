/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:49
 * update_at: 2026-10-05 04:49
 */
// main.cpp：分层图最短路。状态 (i, j, r) = 车在 (i,j)、油箱剩 r 格油的最小费用。
// 行驶 / 强制加油 / 增设油库三类非负权转移，堆优化 Dijkstra，弹出终点即答案。

#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
typedef long long ll;

using namespace std;

const ll MAXN = 105;   // 网格最大边长

ll n, k, A, B, C;
ll grid[MAXN][MAXN]; // grid[i][j] = 1 表示交叉点 (i,j) 处已设油库
ll dist[MAXN][MAXN][12]; // dist[i][j][r]：车在 (i,j)、剩 r 格油时的最小费用

// 堆节点：struct 只放数据，费用小的先出堆
struct Node {
    ll cost, x, y, r;
    bool operator<(const Node &b) const { return cost > b.cost; } // 小根堆
};

// 四个方向：di, dj 为坐标增量，pay = 1 表示该方向使 X 或 Y 减小、需付 B
ll dirs[4][3] = { {0, 1, 0}, {1, 0, 0}, {0, -1, 1}, {-1, 0, 1} };

void solve() {
    scanf("%lld %lld %lld %lld %lld", &n, &k, &A, &B, &C);
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= n; ++j) scanf("%lld", &grid[i][j]);

    memset(dist, 0x3f, sizeof(dist)); // 0x3f3f3f... 充当 INF：远大于任何真实费用
    priority_queue<Node> heap;        // 小根堆：(费用, 行, 列, 剩余油量)
    dist[1][1][k] = 0;                // 起点满油出发，费用 0
    Node start; start.cost = 0; start.x = 1; start.y = 1; start.r = k;
    heap.push(start);

    while (!heap.empty()) {
        Node u = heap.top(); heap.pop();
        if (u.cost != dist[u.x][u.y][u.r]) continue; // 过期堆项：该状态已有更小费用
        if (u.x == n && u.y == n) {                  // 弹出终点即全局最小
            printf("%lld\n", u.cost);
            return;
        }

        bool at_station = grid[u.x][u.y] == 1;
        // 遇油库且油不满：必须先加满并付 A，这是唯一后继，不能加满前离开
        bool must_refuel = at_station && u.r < k;
        if (at_station && u.r < k) {          // 强制加油：原地变满油
            ll nc = u.cost + A;
            if (nc < dist[u.x][u.y][k]) {
                dist[u.x][u.y][k] = nc;
                Node v; v.cost = nc; v.x = u.x; v.y = u.y; v.r = k;
                heap.push(v);
            }
        } else if (!at_station && u.r < k) {  // 增设油库付 C（不含油费 A），再加满付 A
            ll nc = u.cost + C + A;
            if (nc < dist[u.x][u.y][k]) {
                dist[u.x][u.y][k] = nc;
                Node v; v.cost = nc; v.x = u.x; v.y = u.y; v.r = k;
                heap.push(v);
            }
        }

        if (!must_refuel && u.r > 0) {
            // 行驶一格耗 1 格油；向左/上（X 或 Y 减小）付 B，向右/下免费
            for (ll d = 0; d < 4; ++d) {
                ll nx = u.x + dirs[d][0], ny = u.y + dirs[d][1];
                if (nx < 1 || nx > n || ny < 1 || ny > n) continue; // 网格外出界
                ll nc = u.cost + (dirs[d][2] ? B : 0);
                if (nc < dist[nx][ny][u.r - 1]) {
                    dist[nx][ny][u.r - 1] = nc;
                    Node v; v.cost = nc; v.x = nx; v.y = ny; v.r = u.r - 1;
                    heap.push(v);
                }
            }
        }
    }
}

int main() {
    solve();
    return 0;
}
