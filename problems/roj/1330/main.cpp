/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:02
 * update_at: 2026-10-05 10:02
 */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

const int N = 105;
const int MOVES = 12;

// dr, dc: 12 种马步，前 8 种是日字，后 4 种是田字
int dr[MOVES] = {-1, -1, 1, 1, -2, -2, 2, 2, -2, -2, 2, 2};
int dc[MOVES] = {-2, 2, -2, 2, -1, 1, -1, 1, -2, 2, -2, 2};

int dist[N][N]; // dist[r][c] 表示 (r,c) 到 (1,1) 的最少步数

struct Node {
    int r;
    int c;
};

queue<Node> q;

// 从 (1,1) 反向 BFS，建立全图距离表
void bfs() {
    memset(dist, -1, sizeof(dist));
    dist[1][1] = 0;
    q.push((Node){1, 1});
    while (!q.empty()) {
        Node u = q.front();
        q.pop();
        for (int k = 0; k < MOVES; k++) {
            int nr = u.r + dr[k];
            int nc = u.c + dc[k];
            if (nr < 1 || nr > 100 || nc < 1 || nc > 100) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[u.r][u.c] + 1;
            q.push((Node){nr, nc});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    bfs();

    int ar, ac, br, bc;
    cin >> ar >> ac;
    cin >> br >> bc;
    cout << dist[ar][ac] << "\n";
    cout << dist[br][bc] << "\n";

    return 0;
}
