/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:02
 * update_at: 2026-10-05 07:02
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXK = 100005;

ll N, K;

int dist[2 * MAXK + 5]; // dist[x] 表示从 N 到坐标 x 的最少分钟数，-1 兼作“未访问”标记
queue<ll> bfs_queue;    // 待扩展的坐标

// 把坐标看成点、三种操作看成长度 1 的边，问题就是无权图上 N 到 K 的最短路。
// BFS 逐层扩展，第一次到达的层号即为最短距离。
ll bfs() {
    ll limit = 2 * K; // 上界：越过 2K 后想回到 K 至少要走 > K 步，不如从 N 一路 +1 的 K-N 步
    for (ll x = 0; x <= limit; x++) {
        dist[x] = -1;
    }
    dist[N] = 0;
    bfs_queue.push(N);

    while (!bfs_queue.empty()) {
        ll x = bfs_queue.front();
        bfs_queue.pop();

        // 三种操作：走到 x-1、x+1、2x
        ll nxt[3];
        nxt[0] = x - 1;
        nxt[1] = x + 1;
        nxt[2] = 2 * x;

        for (int i = 0; i < 3; i++) {
            ll y = nxt[i];
            if (y < 0 || y > limit) continue;
            if (dist[y] >= 0) continue;
            dist[y] = dist[x] + 1;
            if (y == K) return dist[y]; // 逐层扩展，首次到达即最少分钟数
            bfs_queue.push(y);
        }
    }
    return dist[K];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    if (K <= N) {
        // 向下的操作只有 -1（+1 与 *2 都不降），故答案就是一路减过去
        cout << N - K << "\n";
        return 0;
    }

    cout << bfs() << "\n";
    return 0;
}
