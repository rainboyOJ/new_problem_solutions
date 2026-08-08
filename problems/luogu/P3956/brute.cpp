// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 8;
const int INF = 1e9;

struct Node {
    int x, y;
    int color;
    int magic;
    int dist;

    bool operator < (const Node &other) const {
        return dist > other.dist;
    }
};

int board_size, colored_cnt;
int board[MAXM][MAXM];
int dista[MAXM][MAXM][2][2];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool in_board(int x, int y) {
    return x >= 1 && x <= board_size && y >= 1 && y <= board_size;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(board, -1, sizeof(board));

    cin >> board_size >> colored_cnt;
    for (int i = 1; i <= colored_cnt; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        board[x][y] = c;
    }

    if (board[1][1] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 1; i <= board_size; i++) {
        for (int j = 1; j <= board_size; j++) {
            for (int c = 0; c < 2; c++) {
                for (int s = 0; s < 2; s++) {
                    dista[i][j][c][s] = INF;
                }
            }
        }
    }

    // 小数据暴力版：直接在完整状态图上跑最短路。
    priority_queue<Node> pq;
    int start_color = board[1][1];
    dista[1][1][start_color][0] = 0;
    pq.push({1, 1, start_color, 0, 0});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.dist != dista[cur.x][cur.y][cur.color][cur.magic]) continue;

        if (cur.x == board_size && cur.y == board_size) {
            cout << cur.dist << '\n';
            return 0;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            if (!in_board(nx, ny)) continue;

            if (board[nx][ny] != -1) {
                int next_color = board[nx][ny];
                int cost = (cur.color == next_color ? 0 : 1);
                int new_dist = cur.dist + cost;
                if (new_dist < dista[nx][ny][next_color][0]) {
                    dista[nx][ny][next_color][0] = new_dist;
                    pq.push({nx, ny, next_color, 0, new_dist});
                }
                continue;
            }

            if (cur.magic == 1) continue;

            for (int next_color = 0; next_color <= 1; next_color++) {
                int new_dist = cur.dist + 2 + (cur.color != next_color);
                if (new_dist < dista[nx][ny][next_color][1]) {
                    dista[nx][ny][next_color][1] = new_dist;
                    pq.push({nx, ny, next_color, 1, new_dist});
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
