/**
 * Problem: luogu P7963 - [NOIP2021] 棋局 (Brute Force Verifier)
 * Author: rainboy
 * Date: 2026-11-11 00:55
 * Description: 独立实现的网格可达性遍历检验器
 */
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>

using namespace std;

const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, -1, 1};

struct Piece {
    int col;
    int lv;
};

int n, m, q;
vector<vector<int>> r_edge, d_edge;
vector<vector<Piece>> board;

int get_edge(int x, int y, int dir) {
    if (dir == 0) return (x > 1 ? d_edge[x - 1][y] : 0);
    if (dir == 1) return (x < n ? d_edge[x][y] : 0);
    if (dir == 2) return (y > 1 ? r_edge[x][y - 1] : 0);
    if (dir == 3) return (y < m ? r_edge[x][y] : 0);
    return 0;
}

bool can_eat(int my_col, int my_lv, int tx, int ty) {
    if (board[tx][ty].col == -1) return false;
    return (board[tx][ty].col != my_col && my_lv >= board[tx][ty].lv);
}

void solve_brute() {
    cin >> n >> m >> q;
    r_edge.assign(n + 1, vector<int>(m + 1, 0));
    d_edge.assign(n + 1, vector<int>(m + 1, 0));
    board.assign(n + 1, vector<Piece>(m + 1, {-1, 0}));

    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j < m; ++j) r_edge[i][j] = s[j - 1] - '0';
    }
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j) d_edge[i][j] = s[j - 1] - '0';
    }

    for (int step = 1; step <= q; ++step) {
        int col, lv, x, y;
        cin >> col >> lv >> x >> y;

        set<pair<int, int>> reach;

        // 1 类道路
        for (int d = 0; d < 4; ++d) {
            if (get_edge(x, y, d) == 1) {
                int nx = x + DX[d], ny = y + DY[d];
                if (board[nx][ny].col == -1 || can_eat(col, lv, nx, ny)) {
                    reach.insert({nx, ny});
                }
            }
        }

        // 2 类道路
        for (int d = 0; d < 4; ++d) {
            int cx = x, cy = y;
            while (get_edge(cx, cy, d) == 2) {
                int nx = cx + DX[d], ny = cy + DY[d];
                if (board[nx][ny].col == -1) {
                    reach.insert({nx, ny});
                    cx = nx; cy = ny;
                } else {
                    if (can_eat(col, lv, nx, ny)) reach.insert({nx, ny});
                    break;
                }
            }
        }

        // 3 类道路
        vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
        queue<pair<int, int>> qu;
        for (int d = 0; d < 4; ++d) {
            if (get_edge(x, y, d) == 3) {
                int nx = x + DX[d], ny = y + DY[d];
                if (board[nx][ny].col == -1) {
                    if (!vis[nx][ny]) {
                        vis[nx][ny] = true;
                        qu.push({nx, ny});
                        reach.insert({nx, ny});
                    }
                } else if (can_eat(col, lv, nx, ny)) {
                    reach.insert({nx, ny});
                }
            }
        }

        while (!qu.empty()) {
            auto [cx, cy] = qu.front();
            qu.pop();

            for (int d = 0; d < 4; ++d) {
                if (get_edge(cx, cy, d) == 3) {
                    int nx = cx + DX[d], ny = cy + DY[d];
                    if (nx == x && ny == y) continue;
                    if (board[nx][ny].col == -1) {
                        if (!vis[nx][ny]) {
                            vis[nx][ny] = true;
                            qu.push({nx, ny});
                            reach.insert({nx, ny});
                        }
                    } else if (can_eat(col, lv, nx, ny)) {
                        reach.insert({nx, ny});
                    }
                }
            }
        }

        board[x][y] = {col, lv};
        cout << reach.size() << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) solve_brute();
    }
    return 0;
}
