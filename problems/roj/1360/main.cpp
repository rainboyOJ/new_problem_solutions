/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:00
 * update_at: 2026-10-05 12:00
 */

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 205; // 题目数据范围 N <= 200

ll n, a, b;
int k[MAXN];        // k[i] 表示第 i 层楼写的数字
int dist[MAXN];     // dist[i] 表示从 a 到 i 的最少按键次数，-1 表示未访问

queue<int> q;

// 从起点 a 开始 BFS，第一次到达某层即为最少按键次数
void bfs() {
    memset(dist, -1, sizeof(dist));
    dist[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int nxt;
        nxt = u + k[u];
        if (nxt <= n && dist[nxt] == -1) {
            dist[nxt] = dist[u] + 1;
            q.push(nxt);
        }
        nxt = u - k[u];
        if (nxt >= 1 && dist[nxt] == -1) {
            dist[nxt] = dist[u] + 1;
            q.push(nxt);
        }
    }
}

int main() {
    scanf("%lld%lld%lld", &n, &a, &b);
    for (int i = 1; i <= n; i++) scanf("%d", &k[i]);
    bfs();
    printf("%d\n", dist[b]);
    return 0;
}
