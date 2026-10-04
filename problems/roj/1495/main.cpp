/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:25
 * update_at: 2026-10-05 04:25
 */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 12;         // n, m <= 10，留一点余量
const int MAXP = 10;         // 门与钥匙的类别数 p <= 10
const int MAXMASK = 1 << MAXP;
const int FREE = -1;         // 相邻两格未出现在输入里：既无门也无墙，自由通行
const int WALL = 0;          // g = 0 表示一堵不可逾越的墙

int n, m, p;

// 方向编号：0 上、1 下、2 左、3 右
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

// gate[r][c][d]：从 (r,c) 朝方向 d 的相邻格间编码。
// FREE = 自由通行，WALL = 墙，g >= 1 = 第 g 类门（双向登记）。
int gate[MAXN][MAXN][4];

// key_mask[r][c]：该格钥匙集合的位掩码，第 q-1 位为 1 表示放着第 q 类钥匙。
int key_mask[MAXN][MAXN];

// dist[r][c][mask]：到达状态 (r,c,mask) 的最少步数，-1 表示该状态还没访问过。
// 距离最大不超过状态总数 10*10*1024，用 int 足够并省内存。
int dist[MAXN][MAXN][MAXMASK];

// 状态 (r,c,mask)：站在格子 (r,c)，手里持有钥匙集合 mask 的那些钥匙。
struct State {
    int r;
    int c;
    int mask;
};

// 在状态图上 BFS：每条边代价都是 1，首次弹出终点即为最短时间；搜完仍未到达返回 -1。
ll bfs() {
    queue<State> q; // BFS 队列，出队顺序按步数从小到大

    int start_mask = key_mask[1][1]; // 起点 (1,1) 的钥匙顺手拿走
    dist[1][1][start_mask] = 0;
    State first;
    first.r = 1;
    first.c = 1;
    first.mask = start_mask;
    q.push(first);

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.r == n && cur.c == m) {
            return dist[cur.r][cur.c][cur.mask];
        }

        int nxt_step = dist[cur.r][cur.c][cur.mask] + 1;
        for (int d = 0; d < 4; d++) {
            int r2 = cur.r + dr[d];
            int c2 = cur.c + dc[d];
            if (r2 < 1 || r2 > n || c2 < 1 || c2 > m) {
                continue;
            }

            int g = gate[cur.r][cur.c][d];
            if (g == WALL) {
                continue; // 墙永远不能穿过
            }
            if (g >= 1 && ((cur.mask >> (g - 1)) & 1) == 0) {
                continue; // 是门，但手里没有这一类钥匙，开门不消耗钥匙
            }

            int new_mask = cur.mask | key_mask[r2][c2]; // 落脚后拾取该格钥匙，拿钥匙不耗时
            if (dist[r2][c2][new_mask] != -1) {
                continue; // 状态只入队一次，同一个状态决不会被重复处理
            }
            dist[r2][c2][new_mask] = nxt_step;

            State next_state;
            next_state.r = r2;
            next_state.c = c2;
            next_state.mask = new_mask;
            q.push(next_state);
        }
    }

    return -1; // 全部状态搜完仍到不了 (n,m)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(gate, FREE, sizeof(gate)); // 未登记的相邻格统一置成 -1，即自由通行
    memset(dist, -1, sizeof(dist));

    cin >> n >> m >> p;

    int k;
    cin >> k;
    for (int i = 1; i <= k; i++) {
        int x1, y1, x2, y2, g;
        cin >> x1 >> y1 >> x2 >> y2 >> g;

        // 题目保证两格相邻，先由相对位置定出双向的方向编号
        int d1, d2;
        if (x1 == x2) {
            if (y2 == y1 + 1) {
                d1 = 3; // (x1,y1) -> 右
                d2 = 2; // (x2,y2) -> 左
            } else {
                d1 = 2;
                d2 = 3;
            }
        } else {
            if (x2 == x1 + 1) {
                d1 = 1; // (x1,y1) -> 下
                d2 = 0; // (x2,y2) -> 上
            } else {
                d1 = 0;
                d2 = 1;
            }
        }
        gate[x1][y1][d1] = g;
        gate[x2][y2][d2] = g; // 门和墙都是双向的，两个方向都要登记
    }

    int s;
    cin >> s;
    for (int i = 1; i <= s; i++) {
        int x, y, q;
        cin >> x >> y >> q;
        key_mask[x][y] |= 1 << (q - 1); // 同类钥匙重复出现没有额外作用，用或运算合并
    }

    cout << bfs() << "\n";

    return 0;
}
