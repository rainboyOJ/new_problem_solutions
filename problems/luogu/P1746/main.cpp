#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
char g[MAXN][MAXN];
int dista[MAXN][MAXN];
int x1_pos, y1_pos, x2_pos, y2_pos;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int bfs() {
    queue<Node> q;
    dista[x1_pos][y1_pos] = 0;
    q.push((Node){x1_pos, y1_pos});

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        if (u.x == x2_pos && u.y == y2_pos) {
            return dista[u.x][u.y];
        }

        for (int i = 0; i < 4; i++) {
            int nx = u.x + dx[i];
            int ny = u.y + dy[i];

            if (!in_board(nx, ny)) {
                continue;
            }
            if (g[nx][ny] == '1') {
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

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }
    cin >> x1_pos >> y1_pos >> x2_pos >> y2_pos;

    memset(dista, -1, sizeof(dista));
    cout << bfs() << '\n';
    return 0;
}
