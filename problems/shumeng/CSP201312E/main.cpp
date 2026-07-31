/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXR = 55;
const int MAXC = 55;

int R, C;
char grid[MAXR][MAXC];
bool from_start[MAXR][MAXC], to_target[MAXR][MAXC];
vector<pair<int, int> > reverse_edge[MAXR][MAXC];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool inside(int r, int c) {
    return r >= 1 && r <= R && c >= 1 && c <= C;
}

bool allow_direction(char cell, int direction) {
    if (cell == '-' && direction < 2) {
        return false;
    }
    if (cell == '|' && direction >= 2) {
        return false;
    }
    if (cell == '.' && direction != 1) {
        return false;
    }
    return true;
}

void bfs_from_start(int start_r, int start_c) {
    queue<pair<int, int> > q;
    from_start[start_r][start_c] = true;
    q.push(make_pair(start_r, start_c));

    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        int r = now.first;
        int c = now.second;
        for (int direction = 0; direction < 4; direction++) {
            if (!allow_direction(grid[r][c], direction)) {
                continue;
            }

            int nr = r + dr[direction];
            int nc = c + dc[direction];
            if (!inside(nr, nc) || grid[nr][nc] == '#' || from_start[nr][nc]) {
                continue;
            }

            from_start[nr][nc] = true;
            q.push(make_pair(nr, nc));
        }
    }
}

void bfs_to_target(int target_r, int target_c) {
    queue<pair<int, int> > q;
    to_target[target_r][target_c] = true;
    q.push(make_pair(target_r, target_c));

    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        int r = now.first;
        int c = now.second;
        for (int i = 0; i < (int)reverse_edge[r][c].size(); i++) {
            int pre_r = reverse_edge[r][c][i].first;
            int pre_c = reverse_edge[r][c][i].second;
            if (to_target[pre_r][pre_c]) {
                continue;
            }

            to_target[pre_r][pre_c] = true;
            q.push(make_pair(pre_r, pre_c));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    int start_r = 0, start_c = 0, target_r = 0, target_c = 0;

    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == 'S') {
                start_r = r;
                start_c = c;
            }
            if (grid[r][c] == 'T') {
                target_r = r;
                target_c = c;
            }
        }
    }

    // 建反图：原图中 (r, c) 能到 (nr, nc)，就记录其反向前驱。
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            if (grid[r][c] == '#') {
                continue;
            }
            for (int direction = 0; direction < 4; direction++) {
                if (!allow_direction(grid[r][c], direction)) {
                    continue;
                }

                int nr = r + dr[direction];
                int nc = c + dc[direction];
                if (!inside(nr, nc) || grid[nr][nc] == '#') {
                    continue;
                }
                reverse_edge[nr][nc].push_back(make_pair(r, c));
            }
        }
    }

    bfs_from_start(start_r, start_c);
    if (!from_start[target_r][target_c]) {
        cout << "I'm stuck!\n";
        return 0;
    }

    bfs_to_target(target_r, target_c);
    int answer = 0;
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            if (from_start[r][c] && !to_target[r][c]) {
                answer++;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
