#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 把“每次盖章”当作一次精确覆盖操作，回溯判断能否刚好覆盖所有黑格。
struct Point {
    int x, y;
};

bool dfs(vector<string> &paper, const vector<Point> &stamp_cells, int n, int m, int a, int b) {
    int sx = -1, sy = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (paper[i][j] == 'x') {
                sx = i;
                sy = j;
                break;
            }
        }
        if (sx != -1) {
            break;
        }
    }

    if (sx == -1) {
        return true;
    }

    for (int id = 0; id < (int)stamp_cells.size(); id++) {
        int top = sx - stamp_cells[id].x;
        int left = sy - stamp_cells[id].y;

        bool ok = true;
        vector<Point> covered;

        for (int k = 0; k < (int)stamp_cells.size(); k++) {
            int nx = top + stamp_cells[k].x;
            int ny = left + stamp_cells[k].y;
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || paper[nx][ny] != 'x') {
                ok = false;
                break;
            }
            covered.push_back({nx, ny});
        }

        if (!ok) {
            continue;
        }

        for (int k = 0; k < (int)covered.size(); k++) {
            paper[covered[k].x][covered[k].y] = '.';
        }
        if (dfs(paper, stamp_cells, n, m, a, b)) {
            return true;
        }
        for (int k = 0; k < (int)covered.size(); k++) {
            paper[covered[k].x][covered[k].y] = 'x';
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int n, m, a, b;
        cin >> n >> m >> a >> b;

        vector<string> paper(n), stamp(a);
        for (int i = 0; i < n; i++) {
            cin >> paper[i];
        }
        for (int i = 0; i < a; i++) {
            cin >> stamp[i];
        }

        vector<Point> stamp_cells;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                if (stamp[i][j] == 'x') {
                    stamp_cells.push_back({i, j});
                }
            }
        }

        bool ok;
        if (stamp_cells.empty()) {
            ok = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (paper[i][j] == 'x') {
                        ok = false;
                    }
                }
            }
        } else {
            ok = dfs(paper, stamp_cells, n, m, a, b);
        }

        cout << (ok ? "TAK" : "NIE") << '\n';
    }

    return 0;
}
