#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n, m;
char mp[MAXN][MAXN];
int sx, sy;

// brute.cpp：小数据暴力解。
// 把原迷宫向四周复制很多份，起点放在中间那份里，
// 如果能走到这个大盒子的边界，就认为可以无限走远。

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x, y;
};

int norm_x(int x) {
    x %= n;
    if (x < 0) x += n;
    return x;
}

int norm_y(int y) {
    y %= m;
    if (y < 0) y += m;
    return y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m) {
        sx = -1;
        sy = -1;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                mp[i][j] = s[j];
                if (mp[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        int tile_radius = n * m + 1;
        int H = (tile_radius * 2 + 1) * n;
        int W = (tile_radius * 2 + 1) * m;

        vector<string> big(H, string(W, '#'));
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                char c = mp[i % n][j % m];
                if (c == 'S') c = '.';
                big[i][j] = c;
            }
        }

        int start_x = tile_radius * n + sx;
        int start_y = tile_radius * m + sy;

        vector<vector<char> > vis(H, vector<char>(W, 0));
        queue<Node> q;
        vis[start_x][start_y] = 1;
        q.push({start_x, start_y});

        bool ok = false;

        while (!q.empty()) {
            Node cur = q.front();
            q.pop();

            // 能到达大盒子边界，说明可以走得足够远，
            // 对于这个规模的盒子，就等价于能无限走远。
            if (cur.x == 0 || cur.x == H - 1 || cur.y == 0 || cur.y == W - 1) {
                ok = true;
                break;
            }

            for (int k = 0; k < 4; k++) {
                int nx = cur.x + dx[k];
                int ny = cur.y + dy[k];
                if (nx < 0 || nx >= H || ny < 0 || ny >= W) {
                    continue;
                }
                if (vis[nx][ny] || big[nx][ny] == '#') {
                    continue;
                }
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }

        if (ok) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }

    return 0;
}
