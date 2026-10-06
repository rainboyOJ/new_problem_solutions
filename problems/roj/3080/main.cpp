/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:40
 * update_at: 2026-10-06 11:40
 */

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXC = 155;
const int MAXR = 155;

int C, R;
char g[MAXR][MAXC]; // 网格地图
int dist[MAXR][MAXC]; // dist[r][c] = 从起点到(r,c)的最少跳跃次数，-1表示未访问

// 马走日的8个位移
const int dr[8] = { 1, 1, -1, -1, 2, 2, -2, -2 };
const int dc[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };

struct Node {
    int r, c;
};

queue<Node> q;

int bfs(int sr, int sc) {
    memset(dist, -1, sizeof(dist));
    dist[sr][sc] = 0;
    q.push((Node){sr, sc});
    while (!q.empty()) {
        Node u = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nr = u.r + dr[i];
            int nc = u.c + dc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue; // 越界
            if (g[nr][nc] == '*') continue; // 障碍
            if (dist[nr][nc] != -1) continue; // 已访问
            if (g[nr][nc] == 'H') // 首次到达草地即最少跳跃次数
                return dist[u.r][u.c] + 1;
            dist[nr][nc] = dist[u.r][u.c] + 1;
            q.push((Node){nr, nc});
        }
    }
    return -1; // 题目保证有解，不会走到这里
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> C >> R;
    int sr = -1, sc = -1;
    for (int i = 0; i < R; i++) {
        cin >> g[i];
        for (int j = 0; j < C; j++) {
            if (g[i][j] == 'K') {
                sr = i;
                sc = j;
            }
        }
    }
    cout << bfs(sr, sc) << "\n";
    return 0;
}
