#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int INF = 0x3f3f3f3f;

int n, m;
int obs[MAXN][MAXN];
int dist_arr[MAXN][MAXN][4];

int sx, sy, tx, ty;
string dir_name;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Node {
    int x, y, dir;
};

int get_dir_id(const string &s) {
    if (s == "E") return 0;
    if (s == "S") return 1;
    if (s == "W") return 2;
    return 3;
}

bool can_stand_here(int x, int y) {
    if (x < 1 || x >= n || y < 1 || y >= m) {
        return false;
    }

    // 直接现场检查四个相邻方格是否有障碍。
    if (obs[x][y] || obs[x - 1][y] || obs[x][y - 1] || obs[x - 1][y - 1]) {
        return false;
    }
    return true;
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

    if (!can_stand_here(sx, sy) || !can_stand_here(tx, ty)) {
        cout << -1 << '\n';
        return 0;
    }

    memset(dist_arr, 0x3f, sizeof(dist_arr));
    queue<Node> q;

    int start_dir = get_dir_id(dir_name);
    dist_arr[sx][sy][start_dir] = 0;
    q.push({sx, sy, start_dir});

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        int d = dist_arr[cur.x][cur.y][cur.dir];
        if (cur.x == tx && cur.y == ty) {
            cout << d << '\n';
            return 0;
        }

        int left_dir = (cur.dir + 3) % 4;
        if (dist_arr[cur.x][cur.y][left_dir] > d + 1) {
            dist_arr[cur.x][cur.y][left_dir] = d + 1;
            q.push({cur.x, cur.y, left_dir});
        }

        int right_dir = (cur.dir + 1) % 4;
        if (dist_arr[cur.x][cur.y][right_dir] > d + 1) {
            dist_arr[cur.x][cur.y][right_dir] = d + 1;
            q.push({cur.x, cur.y, right_dir});
        }

        for (int step = 1; step <= 3; step++) {
            int nx = cur.x + dx[cur.dir] * step;
            int ny = cur.y + dy[cur.dir] * step;
            if (!can_stand_here(nx, ny)) {
                break;
            }
            if (dist_arr[nx][ny][cur.dir] > d + 1) {
                dist_arr[nx][ny][cur.dir] = d + 1;
                q.push({nx, ny, cur.dir});
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
