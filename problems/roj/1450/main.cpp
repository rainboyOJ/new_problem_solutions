/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:55
 * update_at: 2026-10-05 23:55
 */
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXL = 305;

int L;                          // 棋盘大小 L×L
int dist[MAXL][MAXL];           // dist[x][y] 表示起点到 (x,y) 的最少步数，-1 表示未访问
int sx, sy, tx, ty;             // 起点与终点坐标

// 骑士的 8 个马步位移
const int fx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
const int fy[8] = {2, -2, 2, -2, 1, -1, 1, -1};

// BFS 求起点到终点的最少马步数
int bfs() {
    if (sx == tx && sy == ty)
        return 0;               // 起点即终点，0 步

    queue< pair<int,int> > q;
    memset(dist, -1, sizeof(dist));
    dist[sx][sy] = 0;
    q.push(make_pair(sx, sy));

    while (!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;

        // 枚举 8 个马步后继
        for (int i = 0; i < 8; ++i) {
            int nx = x + fx[i];
            int ny = y + fy[i];
            if (nx < 0 || nx >= L || ny < 0 || ny >= L)
                continue;       // 越界跳过
            if (dist[nx][ny] != -1)
                continue;       // 已访问过
            dist[nx][ny] = dist[x][y] + 1;
            if (nx == tx && ny == ty)
                return dist[nx][ny]; // 首次到达终点即最短
            q.push(make_pair(nx, ny));
        }
    }
    return -1;                  // 题目保证连通，不会到这里
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &L);
        scanf("%d %d", &sx, &sy);
        scanf("%d %d", &tx, &ty);
        printf("%d\n", bfs());
    }
    return 0;
}
