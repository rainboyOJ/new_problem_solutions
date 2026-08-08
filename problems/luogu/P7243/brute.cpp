#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int MAXN = 15;

int n, m;
ull cur[MAXN][MAXN], nxt[MAXN][MAXN];
int target_x, target_y;
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

// 模拟一天，并返回矩阵是否真的发生了变化。
bool transform_once() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ull g = cur[i][j];
            for (int k = 1; k <= 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (in_board(nx, ny)) {
                    g = gcd(g, cur[nx][ny]);
                }
            }
            nxt[i][j] = g;
        }
    }

    bool changed = false;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (cur[i][j] != nxt[i][j]) {
                changed = true;
            }
            cur[i][j] = nxt[i][j];
        }
    }
    return changed;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> cur[i][j];
        }
    }
    cin >> target_x >> target_y;

    // 曼哈顿半径超过整个棋盘后，答案就不会再变化了。
    for (int day = 0; day <= n + m; day++) {
        if (cur[target_x][target_y] == 1) {
            cout << day << '\n';
            return 0;
        }

        if (!transform_once()) {
            break;
        }
    }
    cout << -1 << '\n';

    return 0;
}
