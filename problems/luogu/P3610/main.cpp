#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int INF = 1e9;

int n;
char grid[MAXN][MAXN];

// 方向顺序：0=上, 1=右, 2=下, 3=左
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct State {
    int x1, y1, d1;
    int x2, y2, d2;
};

int dista[MAXN][MAXN][4][MAXN][MAXN][4];

bool inside(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool blocked(int x, int y) {
    return !inside(x, y) || grid[x][y] == 'H';
}

bool is_goal(int x, int y) {
    return x == 0 && y == n - 1;
}

// 按当前朝向前进一步；如果撞墙或撞干草堆，就停在原地。
void move_forward(int x, int y, int dir, int &nx, int &ny) {
    if (is_goal(x, y)) {
        nx = x;
        ny = y;
        return;
    }

    int tx = x + dx[dir];
    int ty = y + dy[dir];
    if (blocked(tx, ty)) {
        nx = x;
        ny = y;
    } else {
        nx = tx;
        ny = ty;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < n; y1++) {
            for (int d1 = 0; d1 < 4; d1++) {
                for (int x2 = 0; x2 < n; x2++) {
                    for (int y2 = 0; y2 < n; y2++) {
                        for (int d2 = 0; d2 < 4; d2++) {
                            dista[x1][y1][d1][x2][y2][d2] = INF;
                        }
                    }
                }
            }
        }
    }

    queue<State> q;

    // 起点在左下角。题目说初始朝向可能是“上”或“右”，
    // 所以我们同时维护这两种状态。
    State start = {n - 1, 0, 0, n - 1, 0, 1};
    dista[start.x1][start.y1][start.d1][start.x2][start.y2][start.d2] = 0;
    q.push(start);

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        int now = dista[cur.x1][cur.y1][cur.d1][cur.x2][cur.y2][cur.d2];

        if (is_goal(cur.x1, cur.y1) && is_goal(cur.x2, cur.y2)) {
            cout << now << '\n';
            return 0;
        }

        // 操作 1：左转
        State next1 = cur;
        next1.d1 = (next1.d1 + 3) % 4;
        next1.d2 = (next1.d2 + 3) % 4;
        if (dista[next1.x1][next1.y1][next1.d1][next1.x2][next1.y2][next1.d2] == INF) {
            dista[next1.x1][next1.y1][next1.d1][next1.x2][next1.y2][next1.d2] = now + 1;
            q.push(next1);
        }

        // 操作 2：右转
        State next2 = cur;
        next2.d1 = (next2.d1 + 1) % 4;
        next2.d2 = (next2.d2 + 1) % 4;
        if (dista[next2.x1][next2.y1][next2.d1][next2.x2][next2.y2][next2.d2] == INF) {
            dista[next2.x1][next2.y1][next2.d1][next2.x2][next2.y2][next2.d2] = now + 1;
            q.push(next2);
        }

        // 操作 3：前进
        State next3 = cur;
        move_forward(cur.x1, cur.y1, cur.d1, next3.x1, next3.y1);
        move_forward(cur.x2, cur.y2, cur.d2, next3.x2, next3.y2);
        if (dista[next3.x1][next3.y1][next3.d1][next3.x2][next3.y2][next3.d2] == INF) {
            dista[next3.x1][next3.y1][next3.d1][next3.x2][next3.y2][next3.d2] = now + 1;
            q.push(next3);
        }
    }

    return 0;
}
