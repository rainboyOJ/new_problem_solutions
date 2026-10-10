/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:29
 * update_at: 2026-10-07 15:29
 */
// 1687 积水问题：二维接雨水的推广，外围是「无限大且高度为 0」的区域。
// 一个格子的积水高度 = 逃逸水位 - 地形高度，而逃逸水位是
// 「从该格子走到外围的所有路径上，路径最大地形高度」的最小值（minimax 路径）。
// 求 minimax 用多源 Dijkstra：所有边界格子以 max(h,0) 为初始水位入堆，
// 每次弹出水位最小的格子，向四个方向松弛 nd = max(当前水位, 邻居地形高度)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;
const ll INF = (1LL << 62);

int n, m;              // 土地的行数、列数
ll h[MAXN][MAXN];      // h[i][j] 是第 i 行第 j 列小块的地形高度
ll level[MAXN][MAXN];  // level[i][j] 是逃逸水位：从 (i,j) 逃到外围的路径上最大高度的最小值
char done[MAXN][MAXN]; // 该格子的逃逸水位是否已经确定（Dijkstra 出堆标记）

const int di[4] = {1, -1, 0, 0};
const int dj[4] = {0, 0, 1, -1};

// 小根堆的结点：水位 d，格子编号 id = i * m + j
struct Node {
    ll d;
    int id;

    // priority_queue 默认大根堆，把比较反过来就得到小根堆
    bool operator<(const Node &other) const {
        return d > other.d;
    }
};

priority_queue<Node> pq;

// 多源 Dijkstra 求每个格子的逃逸水位
void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            level[i][j] = INF;
            done[i][j] = 0;
        }
    }

    // 外围高度为 0，边界格子直接挨着外围，所以水位至少是 max(h, 0)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                level[i][j] = max(h[i][j], 0LL);
                pq.push(Node{level[i][j], i * m + j});
            }
        }
    }

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        int i = cur.id / m;
        int j = cur.id % m;
        if (done[i][j]) continue; // 同一格子可能入堆多次，只处理水位最小的那一次
        done[i][j] = 1;

        for (int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if (done[ni][nj]) continue;
            ll nd = max(cur.d, h[ni][nj]); // 走这条边，水位被沿途更高的地形顶起来
            if (nd < level[ni][nj]) {
                level[ni][nj] = nd;
                pq.push(Node{nd, ni * m + nj});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%lld%c", level[i][j] - h[i][j], j + 1 == m ? '\n' : ' ');
        }
    }
}

int main() {
    if (scanf("%d %d", &n, &m) != 2) return 0;
    if (n <= 0 || m <= 0) return 0; // 没有小块，没有输出
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lld", &h[i][j]);
        }
    }
    solve();
    return 0;
}
