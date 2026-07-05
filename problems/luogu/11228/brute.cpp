// brute.cpp：小数据暴力解，严格按题意逐步模拟机器人的动作。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m, k;
int x, y, d;
char grid_map[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool can_go(int nx, int ny) {
    return 1 <= nx && nx <= n && 1 <= ny && ny <= m && grid_map[nx][ny] == '.';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        cin >> x >> y >> d;
        for (int i = 1; i <= n; i++) {
            string row;
            cin >> row;
            for (int j = 1; j <= m; j++) {
                grid_map[i][j] = row[j - 1];
                visited[i][j] = false;
            }
        }

        int answer = 1;
        visited[x][y] = true;

        for (int step = 1; step <= k; step++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (can_go(nx, ny)) {
                x = nx;
                y = ny;
                if (!visited[x][y]) {
                    visited[x][y] = true;
                    answer++;
                }
            } else {
                d = (d + 1) % 4;
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
