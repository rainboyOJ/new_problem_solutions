/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 23:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int m, n;             // 画布宽度与高度（以字符为单位）
char board[MAXN][MAXN]; // board[y][x] 保存画布，初始全为 '.'

// 在 (x1,y1) 到 (x2,y2) 之间画水平或竖直线段。
// 遇到另一方向的线段时改为 '+'.
void draw_line(int x1, int y1, int x2, int y2) {
    if (y1 == y2) { // 水平线段，用 '-'
        if (x1 > x2) swap(x1, x2);
        for (int x = x1; x <= x2; x++) {
            if (board[y1][x] == '|') board[y1][x] = '+';
            else board[y1][x] = '-';
        }
    } else { // 竖直线段，用 '|'
        if (y1 > y2) swap(y1, y2);
        for (int y = y1; y <= y2; y++) {
            if (board[y][x1] == '-') board[y][x1] = '+';
            else board[y][x1] = '|';
        }
    }
}

// 从 (x, y) 四连通填充 color；线段（- | +）是填充边界。
void flood_fill(int x, int y, char color) {
    int visited[MAXN][MAXN] = {};
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    queue<pair<int, int> > cells;
    cells.push(make_pair(x, y));
    visited[y][x] = 1;
    while (!cells.empty()) {
        pair<int, int> current = cells.front();
        cells.pop();
        int cx = current.first, cy = current.second;
        board[cy][cx] = color;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[ny][nx]) continue;
            if (board[ny][nx] == '-' || board[ny][nx] == '|' || board[ny][nx] == '+') continue;
            visited[ny][nx] = 1;
            cells.push(make_pair(nx, ny));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) board[y][x] = '.';
    }

    int q;
    cin >> q;
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 0) { // 画线
            int x2, y2;
            cin >> x2 >> y2;
            draw_line(x, y, x2, y2);
        } else { // 填充
            char color;
            cin >> color;
            flood_fill(x, y, color);
        }
    }

    // 画布左下角是 (0,0)，y 向上增长，因此从高到低输出每一行。
    for (int y = n - 1; y >= 0; y--) {
        for (int x = 0; x < m; x++) cout << board[y][x];
        cout << '\n';
    }
    return 0;
}