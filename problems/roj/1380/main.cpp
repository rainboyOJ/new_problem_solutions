/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:30
 * update_at: 2026-10-05 12:30
 */
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, p, c, m;
vector<int> g[MAXN]; // g[i]：i 号小朋友身旁的人的编号列表
int dist[MAXN];      // dist[i]：糖从 C 传到 i 的最短时间（秒），-1 表示未访问

// 从 C 出发 BFS，求每个人最早拿到糖的时刻（每条边耗时 1 秒）
void bfs() {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[c] = 0;
    queue<int> q;
    q.push(c);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < (int)g[x].size(); i++) {
            int y = g[x][i];
            if (dist[y] == -1) { // 每人只收一次糖
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &p, &c);
    scanf("%d", &m);
    for (int i = 1; i <= p; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    bfs();

    // 第 v 个人在 dist[v]+1 秒收到糖，再吃 m 秒吃完；
    // 最后吃完的一定是离 C 最远的人：ans = max(dist) + m + 1
    int max_dist = 0;
    for (int i = 1; i <= n; i++)
        if (dist[i] > max_dist) max_dist = dist[i];
    printf("%d\n", max_dist + m + 1);
    return 0;
}
