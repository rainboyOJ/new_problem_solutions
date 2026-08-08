#include <bits/stdc++.h>
using namespace std;

const int MAXM = 105;
const int INF = 1e9;

struct Node {
    int x, y;
    int color;   // 当前所站格子的颜色：0 红，1 黄
    int magic;   // 0 表示当前格子本来就有颜色，1 表示当前格子是用魔法临时染色的
    int dist;

    bool operator < (const Node &other) const {
        return dist > other.dist;
    }
};

int board_size, colored_cnt;
int board[MAXM][MAXM];               // -1 表示无色，其它是原始颜色
int dista[MAXM][MAXM][2][2];
bool vis[MAXM][MAXM][2][2];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool in_board(int x, int y) {
    return x >= 1 && x <= board_size && y >= 1 && y <= board_size;
}

void update_state(priority_queue<Node> &pq, int x, int y, int color, int magic, int new_dist) {
    if (new_dist >= dista[x][y][color][magic]) return;
    dista[x][y][color][magic] = new_dist;
    pq.push({x, y, color, magic, new_dist});
}

int dijkstra() {
    for (int i = 1; i <= board_size; i++) {
        for (int j = 1; j <= board_size; j++) {
            for (int c = 0; c < 2; c++) {
                for (int s = 0; s < 2; s++) {
                    dista[i][j][c][s] = INF;
                    vis[i][j][c][s] = false;
                }
            }
        }
    }

    // 起点一开始就必须有颜色，否则无法站在上面。
    if (board[1][1] == -1) return -1;

    priority_queue<Node> pq;
    int start_color = board[1][1];
    dista[1][1][start_color][0] = 0;
    pq.push({1, 1, start_color, 0, 0});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        int x = cur.x;
        int y = cur.y;
        int color = cur.color;
        int magic = cur.magic;

        if (vis[x][y][color][magic]) continue;
        vis[x][y][color][magic] = true;

        if (x == board_size && y == board_size) {
            return cur.dist;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (!in_board(nx, ny)) continue;

            // 下一个格子本来就有颜色，可以直接走过去。
            if (board[nx][ny] != -1) {
                int next_color = board[nx][ny];
                int cost = (color == next_color ? 0 : 1);
                update_state(pq, nx, ny, next_color, 0, cur.dist + cost);
                continue;
            }

            // 下一个格子是无色格，只能在“当前格子不是魔法格”时施法进入。
            if (magic == 1) continue;

            for (int next_color = 0; next_color <= 1; next_color++) {
                int cost = 2; // 施法本身花 2 金币
                if (color != next_color) cost++;
                update_state(pq, nx, ny, next_color, 1, cur.dist + cost);
            }
        }
    }

    return -1;
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

    cout << dijkstra() << '\n';
    return 0;
}
