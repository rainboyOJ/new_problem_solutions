#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int INF = 0x3f3f3f3f;

int n, m;
int obs[MAXN][MAXN];          // 原始障碍格，按题目给出的 N*M 网格存
int can_stand[MAXN][MAXN];    // 机器人中心能否站在这个格点
int dist_arr[MAXN][MAXN][4];  // 最短路：位置 + 朝向

int sx, sy, tx, ty;
string dir_name;

// 方向顺序：东、南、西、北
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Node {
    int x, y, dir;
};

int get_dir_id(const string &s) {
    if (s == "E") return 0;
    if (s == "S") return 1;
    if (s == "W") return 2;
    return 3; // N
}

bool inside_point(int x, int y) {
    // 机器人中心只能站在内部格点，边界上不行。
    return x >= 1 && x < n && y >= 1 && y < m;
}

void build_can_stand() {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < m; y++) {
            // 机器人直径大于 1，所以中心站在格点 (x,y) 时，
            // 周围四个小方格只要有一个是障碍，这个点就不能站。
            if (obs[x][y] || obs[x - 1][y] || obs[x][y - 1] || obs[x - 1][y - 1]) {
                can_stand[x][y] = 0;
            }
            else {
                can_stand[x][y] = 1;
            }
        }
    }
}

int bfs(int start_dir) {
    memset(dist_arr, 0x3f, sizeof(dist_arr));

    if (!inside_point(sx, sy) || !inside_point(tx, ty)) {
        return -1;
    }
    if (!can_stand[sx][sy] || !can_stand[tx][ty]) {
        return -1;
    }

    queue<Node> q;
    dist_arr[sx][sy][start_dir] = 0;
    q.push({sx, sy, start_dir});

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        int now_dist = dist_arr[cur.x][cur.y][cur.dir];
        if (cur.x == tx && cur.y == ty) {
            return now_dist;
        }

        // 左转
        int left_dir = (cur.dir + 3) % 4;
        if (dist_arr[cur.x][cur.y][left_dir] > now_dist + 1) {
            dist_arr[cur.x][cur.y][left_dir] = now_dist + 1;
            q.push({cur.x, cur.y, left_dir});
        }

        // 右转
        int right_dir = (cur.dir + 1) % 4;
        if (dist_arr[cur.x][cur.y][right_dir] > now_dist + 1) {
            dist_arr[cur.x][cur.y][right_dir] = now_dist + 1;
            q.push({cur.x, cur.y, right_dir});
        }

        // 向前走 1/2/3 步，每种指令代价都是 1。
        for (int step = 1; step <= 3; step++) {
            int nx = cur.x + dx[cur.dir] * step;
            int ny = cur.y + dy[cur.dir] * step;

            // 只要中途某一步撞到边界或障碍，后面更远的步数也都不能走了。
            if (!inside_point(nx, ny) || !can_stand[nx][ny]) {
                break;
            }

            if (dist_arr[nx][ny][cur.dir] > now_dist + 1) {
                dist_arr[nx][ny][cur.dir] = now_dist + 1;
                q.push({nx, ny, cur.dir});
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> obs[i][j];
        }
    }
    cin >> sx >> sy >> tx >> ty >> dir_name;

    build_can_stand();
    cout << bfs(get_dir_id(dir_name)) << '\n';

    return 0;
}
