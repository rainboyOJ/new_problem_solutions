/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:13
 * update_at: 2026-10-06 17:13
 */

#include <iostream>
#include <deque>
#include <utility>
using namespace std;

typedef long long ll;

const int MAXR = 505;
const int MAXC = 505;
const int INF = 0x3f3f3f3f;

// 四个斜向邻居：(di, dj, 穿越格子相对当前格点的偏移 ci, cj, 该格需要的方向)
// 方向用字符存储，与读入的 grid[i][j] 直接比较
const int DIR[4][5] = {
    { 1,  1,  0,  0, '\\'}, // 右下，穿过格子 (i, j)，需要 '\'
    { 1, -1,  0, -1,  '/'}, // 左下，穿过格子 (i, j-1)，需要 '/'
    {-1,  1, -1,  0,  '/'}, // 右上，穿过格子 (i-1, j)，需要 '/'
    {-1, -1, -1, -1, '\\'}, // 左上，穿过格子 (i-1, j-1)，需要 '\'
};

char grid[MAXR][MAXC];   // 格子方向，下标从 0 开始
int dist[MAXR][MAXC];    // 格点 (i,j) 的最短距离，格点范围 0..R, 0..C

deque<pair<int, int>> q; // 0-1 BFS 双端队列，存格点坐标

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int R, C;
        cin >> R >> C;
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
        }

        // 初始化距离数组，只清实际用到的范围
        for (int i = 0; i <= R; ++i) {
            for (int j = 0; j <= C; ++j) {
                dist[i][j] = INF;
            }
        }
        while (!q.empty()) q.pop_back();

        dist[0][0] = 0;
        q.push_back(make_pair(0, 0));

        while (!q.empty()) {
            pair<int, int> cur = q.front();
            q.pop_front();
            int i = cur.first;
            int j = cur.second;
            int d = dist[i][j];
            if (i == R && j == C) break; // 终点出队时距离已定型

            for (int k = 0; k < 4; ++k) {
                int ni = i + DIR[k][0];
                int nj = j + DIR[k][1];
                if (ni < 0 || ni > R || nj < 0 || nj > C) continue;
                int ci = i + DIR[k][2];
                int cj = j + DIR[k][3];
                int want = DIR[k][4];
                int w = (grid[ci][cj] != want) ? 1 : 0; // 方向不对代价为 1
                int nd = d + w;
                if (nd < dist[ni][nj]) {
                    dist[ni][nj] = nd;
                    if (w == 0) {
                        q.push_front(make_pair(ni, nj)); // 0 权边放队头
                    } else {
                        q.push_back(make_pair(ni, nj));  // 1 权边放队尾
                    }
                }
            }
        }

        if (dist[R][C] == INF) {
            cout << "NO SOLUTION\n";
        } else {
            cout << dist[R][C] << "\n";
        }
    }
    return 0;
}
