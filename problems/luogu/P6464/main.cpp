/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 14:55
 */
// 传送门：只能装一对、把两栋楼之间距离变成 0，求安装后所有无序点对最短路之和的最小值。
// 传送门等价于在 a、b 之间加一条权为 0 的双向边。不必为每个候选重跑 Floyd：
//   不用这条新边：原图边全在，距离仍是原矩阵的 d[x][y]（最优子结构，d 表直接复用）；
//   用这条新边：权为 0，所以多次经过可化简成一次，且传送门双向，只有两个方向。
// 于是新距离就是三个候选取最小：
//   d'[x][y] = min(d[x][y], d[x][a] + d[b][y], d[x][b] + d[a][y])
// 每对 (x,y) 只花 O(1)，整体 O(n^3) 一次 Floyd + O(n^4) 枚举。
// 注意：(a,b) 这一对本身也要计入总和，装传送门后它是 0。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;         // 点数上界 n <= 100
const long long INF = (1LL << 60);

int n, m;
long long dist_node[MAXN][MAXN];  // 原图任意两点最短路；dist_node[i][i] = 0

void floyd() {
    for (int middle = 1; middle <= n; middle++) {
        for (int start = 1; start <= n; start++) {
            // 若 start 到 middle 都不可达，后面整轮都不用试
            if (dist_node[start][middle] == INF) continue;
            long long base = dist_node[start][middle];
            for (int finish = 1; finish <= n; finish++) {
                long long candidate = base + dist_node[middle][finish];
                if (candidate < dist_node[start][finish]) {
                    dist_node[start][finish] = candidate;
                }
            }
        }
    }
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist_node[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // 题面保证无重边无自环，直接赋值即可
        dist_node[u][v] = w;
        dist_node[v][u] = w;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    floyd();

    long long answer = INF;
    for (int first = 1; first <= n; first++) {
        for (int second = first + 1; second <= n; second++) {
            long long total = 0;
            for (int x = 1; x <= n; x++) {
                for (int y = x + 1; y <= n; y++) {
                    // 不用传送门 / 经 first->second / 经 second->first，三者取最小
                    long long best = dist_node[x][y];
                    long long through_first = dist_node[x][first] + dist_node[second][y];
                    long long through_second = dist_node[x][second] + dist_node[first][y];
                    if (through_first < best) best = through_first;
                    if (through_second < best) best = through_second;
                    total += best;
                }
            }
            if (total < answer) answer = total;
        }
    }

    cout << answer << '\n';
    return 0;
}
