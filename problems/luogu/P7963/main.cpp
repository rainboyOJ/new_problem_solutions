/**
 * Problem: luogu P7963 - [NOIP2021] 棋局
 * Author: rainboy
 * Date: 2026-11-11 00:55
 * Description: 在线三类道路多源连通块与吃子合法性去重判定
 */
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// 方向：0:上, 1:下, 2:左, 3:右
const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, -1, 1};

struct Piece {
    int col; // 0:黑, 1:白, -1:无
    int lv;
};

int n, m, q;
// 道路类型：r_edge[i][j] 为 (i,j) 与 (i,j+1) 间的道路 (1<=j<m)
// d_edge[i][j] 为 (i,j) 与 (i+1,j) 间的道路 (1<=i<n)
vector<vector<int>> r_edge;
vector<vector<int>> d_edge;
vector<vector<Piece>> board;

// 获取 (x, y) 沿方向 dir 的道路类型，若越界返回 0
int get_edge(int x, int y, int dir) {
    if (dir == 0) { // 上: (x-1, y) 到 (x, y)
        if (x <= 1) return 0;
        return d_edge[x - 1][y];
    }
    if (dir == 1) { // 下: (x, y) 到 (x+1, y)
        if (x >= n) return 0;
        return d_edge[x][y];
    }
    if (dir == 2) { // 左: (x, y-1) 到 (x, y)
        if (y <= 1) return 0;
        return r_edge[x][y - 1];
    }
    if (dir == 3) { // 右: (x, y) 到 (x, y+1)
        if (y >= m) return 0;
        return r_edge[x][y];
    }
    return 0;
}

// 检查能否吃掉目标格点上的棋子
bool can_capture(int my_col, int my_lv, int target_x, int target_y) {
    const Piece &target = board[target_x][target_y];
    if (target.col == -1) return false;
    return (target.col != my_col && my_lv >= target.lv);
}

void solve() {
    cin >> n >> m >> q;

    r_edge.assign(n + 1, vector<int>(m + 1, 0));
    d_edge.assign(n + 1, vector<int>(m + 1, 0));
    board.assign(n + 1, vector<Piece>(m + 1, {-1, 0}));

    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j < m; ++j) {
            r_edge[i][j] = s[j - 1] - '0';
        }
    }

    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j) {
            d_edge[i][j] = s[j - 1] - '0';
        }
    }

    vector<vector<int>> mark_tag(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> bfs_vis(n + 1, vector<int>(m + 1, 0));
    int cur_tag = 0;

    for (int step = 1; step <= q; ++step) {
        int col, lv, x, y;
        cin >> col >> lv >> x >> y;

        cur_tag++;
        int reachable_count = 0;

        auto add_reachable = [&](int rx, int ry) {
            if (mark_tag[rx][ry] != cur_tag) {
                mark_tag[rx][ry] = cur_tag;
                reachable_count++;
            }
        };

        // 1. 处理 1 类道路：只能走 1 步
        for (int dir = 0; dir < 4; ++dir) {
            if (get_edge(x, y, dir) == 1) {
                int nx = x + DX[dir];
                int ny = y + DY[dir];
                if (board[nx][ny].col == -1) {
                    add_reachable(nx, ny);
                } else if (can_capture(col, lv, nx, ny)) {
                    add_reachable(nx, ny);
                }
            }
        }

        // 2. 处理 2 类道路：沿 4 个方向直线行走
        for (int dir = 0; dir < 4; ++dir) {
            int cx = x;
            int cy = y;
            while (get_edge(cx, cy, dir) == 2) {
                int nx = cx + DX[dir];
                int ny = cy + DY[dir];
                if (board[nx][ny].col == -1) {
                    add_reachable(nx, ny);
                    cx = nx;
                    cy = ny;
                } else {
                    if (can_capture(col, lv, nx, ny)) {
                        add_reachable(nx, ny);
                    }
                    break;
                }
            }
        }

        // 3. 处理 3 类道路：连通块可拐弯行走
        queue<pair<int, int>> q_bfs;
        for (int dir = 0; dir < 4; ++dir) {
            if (get_edge(x, y, dir) == 3) {
                int nx = x + DX[dir];
                int ny = y + DY[dir];
                if (board[nx][ny].col == -1) {
                    if (bfs_vis[nx][ny] != cur_tag) {
                        bfs_vis[nx][ny] = cur_tag;
                        q_bfs.push({nx, ny});
                        add_reachable(nx, ny);
                    }
                } else if (can_capture(col, lv, nx, ny)) {
                    add_reachable(nx, ny);
                }
            }
        }

        while (!q_bfs.empty()) {
            auto [cx, cy] = q_bfs.front();
            q_bfs.pop();

            for (int dir = 0; dir < 4; ++dir) {
                if (get_edge(cx, cy, dir) == 3) {
                    int nx = cx + DX[dir];
                    int ny = cy + DY[dir];
                    if (nx == x && ny == y) continue;

                    if (board[nx][ny].col == -1) {
                        if (bfs_vis[nx][ny] != cur_tag) {
                            bfs_vis[nx][ny] = cur_tag;
                            q_bfs.push({nx, ny});
                            add_reachable(nx, ny);
                        }
                    } else if (can_capture(col, lv, nx, ny)) {
                        add_reachable(nx, ny);
                    }
                }
            }
        }

        // 放置此棋子到棋盘上
        board[x][y] = {col, lv};

        cout << reachable_count << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }

    return 0;
}
