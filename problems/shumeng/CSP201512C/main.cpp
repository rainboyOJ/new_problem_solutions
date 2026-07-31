/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:53
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, q;
    cin >> m >> n >> q;
    vector<string> board(n, string(m, '.'));
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 0) {
            int x2, y2;
            cin >> x2 >> y2;
            if (y == y2) {
                if (x > x2) swap(x, x2);
                for (int i = x; i <= x2; i++) board[y][i] = board[y][i] == '|' ? '+' : '-';
            } else {
                if (y > y2) swap(y, y2);
                for (int i = y; i <= y2; i++) board[i][x] = board[i][x] == '-' ? '+' : '|';
            }
        } else {
            char color;
            cin >> color;
            int visited[105][105] = {};
            queue<pair<int, int> > cells;
            cells.push(make_pair(x, y)); visited[y][x] = 1;
            int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
            while (!cells.empty()) {
                pair<int, int> current = cells.front(); cells.pop();
                int cx = current.first, cy = current.second;
                board[cy][cx] = color;
                for (int i = 0; i < 4; i++) {
                    int nx = cx + dx[i], ny = cy + dy[i];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[ny][nx]) continue;
                    if (board[ny][nx] == '-' || board[ny][nx] == '|' || board[ny][nx] == '+') continue;
                    visited[ny][nx] = 1; cells.push(make_pair(nx, ny));
                }
            }
        }
    }
    for (int y = n - 1; y >= 0; y--) cout << board[y] << '\n';
    return 0;
}
