#include <bits/stdc++.h>
using namespace std;

const int LIM = 50;

int x1_pos, y1_pos, x2_pos, y2_pos;
int dx[12] = {-2, -2, -1, -1, 1, 1, 2, 2, -2, -2, 2, 2};
int dy[12] = {-1, 1, -2, 2, -2, 2, -1, 1, -2, 2, -2, 2};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && y >= 1 && x <= LIM && y <= LIM;
}

int solve_one(int sx, int sy) {
    static int dista[LIM + 5][LIM + 5];
    memset(dista, -1, sizeof(dista));

    queue<Node> q;
    dista[sx][sy] = 0;
    q.push((Node){sx, sy});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (u.x == 1 && u.y == 1) {
            return dista[u.x][u.y];
        }

        for (int i = 0; i < 12; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];

            if (!in_board(nx, ny)) {
                continue;
            }
            if (dista[nx][ny] != -1) {
                continue;
            }

            dista[nx][ny] = dista[u.x][u.y] + 1;
            q.push((Node){nx, ny});
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x1_pos >> y1_pos;
    cin >> x2_pos >> y2_pos;

    // 朴素做法：两匹马分别从起点各跑一次 BFS。
    cout << solve_one(x1_pos, y1_pos) << '\n';
    cout << solve_one(x2_pos, y2_pos) << '\n';
    return 0;
}
