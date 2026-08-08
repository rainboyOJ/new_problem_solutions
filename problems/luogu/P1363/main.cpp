#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;

int n, m;
char mp[MAXN][MAXN];

// vis[x][y] 表示这个“模 n、模 m 之后”的格子是否访问过
bool vis[MAXN][MAXN];
// first_x / first_y 记录第一次访问这个模格子时，对应的绝对坐标
int first_x[MAXN][MAXN];
int first_y[MAXN][MAXN];

int sx, sy;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x, y; // 这里存的是无限迷宫中的绝对坐标
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

bool bfs() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vis[i][j] = false;
        }
    }

    queue<Node> q;
    vis[sx][sy] = true;
    first_x[sx][sy] = sx;
    first_y[sx][sy] = sy;
    q.push({sx, sy});

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        for (int k = 0; k < 4; k++) {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];

            int mx = norm_x(nx);
            int my = norm_y(ny);

            if (mp[mx][my] == '#') {
                continue;
            }

            if (!vis[mx][my]) {
                vis[mx][my] = true;
                first_x[mx][my] = nx;
                first_y[mx][my] = ny;
                q.push({nx, ny});
            }
            else {
                // 同一个模格子被两个不同绝对坐标访问到，
                // 说明可以利用平铺结构不断走远。
                if (first_x[mx][my] != nx || first_y[mx][my] != ny) {
                    return true;
                }
            }
        }
    }

    return false;
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

        if (bfs()) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }

    return 0;
}
