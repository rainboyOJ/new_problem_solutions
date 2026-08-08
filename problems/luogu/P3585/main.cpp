#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

int q;

bool solve_one() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    vector<string> paper(n);
    vector<string> stamp(a);
    for (int i = 0; i < n; i++) {
        cin >> paper[i];
    }
    for (int i = 0; i < a; i++) {
        cin >> stamp[i];
    }

    vector<Point> cells;
    int anchor_x = -1;
    int anchor_y = -1;

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (stamp[i][j] == 'x') {
                if (anchor_x == -1) {
                    anchor_x = i;
                    anchor_y = j;
                }
                cells.push_back({i, j});
            }
        }
    }

    int black_cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (paper[i][j] == 'x') {
                black_cnt++;
            }
        }
    }

    if (cells.empty()) {
        return black_cnt == 0;
    }

    vector<Point> offset;
    for (int i = 0; i < (int)cells.size(); i++) {
        offset.push_back({cells[i].x - anchor_x, cells[i].y - anchor_y});
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (paper[i][j] != 'x') {
                continue;
            }

            // 当前最左上的黑格，必须对应印章锚点。
            for (int k = 0; k < (int)offset.size(); k++) {
                int nx = i + offset[k].x;
                int ny = j + offset[k].y;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || paper[nx][ny] != 'x') {
                    return false;
                }
            }

            for (int k = 0; k < (int)offset.size(); k++) {
                int nx = i + offset[k].x;
                int ny = j + offset[k].y;
                paper[nx][ny] = '.';
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> q;
    while (q--) {
        cout << (solve_one() ? "TAK" : "NIE") << '\n';
    }

    return 0;
}
