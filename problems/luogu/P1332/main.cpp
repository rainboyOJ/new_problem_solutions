#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n, m, a, b;
int dista[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a >> b;

    memset(dista, -1, sizeof(dista));
    queue<Node> q;

    for (int i = 1; i <= a; i++) {
        int x, y;
        cin >> x >> y;
        if (dista[x][y] == -1) {
            dista[x][y] = 0;
            q.push((Node){x, y});
        }
    }

    while (!q.empty()) {
        Node u = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
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

    for (int i = 1; i <= b; i++) {
        int x, y;
        cin >> x >> y;
        cout << dista[x][y] << '\n';
    }

    return 0;
}
