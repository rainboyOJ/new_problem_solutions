/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:11
 * update_at: 2026-10-05 07:11
 */
// main.cpp：棋盘上马走日的最少步数，按步数分层 BFS 求隐式无权图最短路。
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXL = 305;

ll L;                        // 当前样例的棋盘边长
ll sx, sy, tx, ty;           // 起点、终点的坐标

int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};  // 马的 8 个走法
int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};  // 分别对应 (±1,±2) 与 (±2,±1)

int dist[MAXL][MAXL];        // dist[x][y] = 起点到 (x,y) 的最少步数，-1 表示未访问
struct Node {
    ll x;
    ll y;
};
Node que[MAXL * MAXL];       // BFS 队列：每格入队即标记，至多入队一次

// 从起点 BFS 到终点，首次到达时的步数即最少步数。
ll bfs() {
    if (sx == tx && sy == ty) {
        return 0;
    }
    memset(dist, -1, sizeof(dist));
    ll head = 0;
    ll tail = 0;
    dist[sx][sy] = 0;
    que[tail].x = sx;
    que[tail].y = sy;
    tail++;
    while (head < tail) {
        ll x = que[head].x;
        ll y = que[head].y;
        ll step = dist[x][y] + 1;    // 出队格子的下一层步数
        head++;
        for (int k = 0; k < 8; k++) {
            ll nx = x + dr[k];
            ll ny = y + dc[k];
            if (nx < 0 || nx >= L || ny < 0 || ny >= L) continue;
            if (dist[nx][ny] != -1) continue;
            if (nx == tx && ny == ty) return step;  // BFS 首次到达即最短
            dist[nx][ny] = step;
            que[tail].x = nx;
            que[tail].y = ny;
            tail++;
        }
    }
    return -1;                       // 棋盘够大时马必可达，此处仅兜底
}

int main() {
    ll T;
    scanf("%lld", &T);
    for (ll i = 0; i < T; i++) {
        scanf("%lld", &L);
        scanf("%lld%lld", &sx, &sy);
        scanf("%lld%lld", &tx, &ty);
        printf("%lld\n", bfs());
    }
    return 0;
}
