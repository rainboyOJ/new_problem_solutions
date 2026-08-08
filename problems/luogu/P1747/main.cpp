#include <bits/stdc++.h>
using namespace std;

const int LIM = 50;

int x1_pos, y1_pos, x2_pos, y2_pos;
int dista[LIM + 5][LIM + 5];
int dx[12] = {-2, -2, -1, -1, 1, 1, 2, 2, -2, -2, 2, 2};
int dy[12] = {-1, 1, -2, 2, -2, 2, -1, 1, -2, 2, -2, 2};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && y >= 1 && x <= LIM && y <= LIM;
}

void bfs() {
    queue<Node> q;
    dista[1][1] = 0;
    q.push((Node){1, 1});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

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
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x1_pos >> y1_pos;
    cin >> x2_pos >> y2_pos;

    memset(dista, -1, sizeof(dista));
    bfs();

    cout << dista[x1_pos][y1_pos] << '\n';
    cout << dista[x2_pos][y2_pos] << '\n';
    return 0;
}
