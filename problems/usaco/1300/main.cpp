/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:44
 * update_at: 2026-07-11 16:46
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int test_count;
int n, k;
char target_grid[MAXN][MAXN];
char stamp_grid[4][MAXN][MAXN];
char painted[MAXN][MAXN];

void build_rotations() {
    for (int rot = 1; rot < 4; rot++) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                stamp_grid[rot][i][j] = stamp_grid[rot - 1][k - 1 - j][i];
            }
        }
    }
}

bool can_stamp(int rot, int x, int y) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (stamp_grid[rot][i][j] == '*' && target_grid[x + i][y + j] == '.') {
                return false;
            }
        }
    }
    return true;
}

void do_stamp(int rot, int x, int y) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (stamp_grid[rot][i][j] == '*') {
                painted[x + i][y + j] = '*';
            }
        }
    }
}

bool solve_one() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            target_grid[i][j] = row[j];
            painted[i][j] = '.';
        }
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < k; j++) {
            stamp_grid[0][i][j] = row[j];
        }
    }

    build_rotations();

    for (int rot = 0; rot < 4; rot++) {
        for (int i = 0; i + k <= n; i++) {
            for (int j = 0; j + k <= n; j++) {
                if (can_stamp(rot, i, j)) {
                    do_stamp(rot, i, j);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (painted[i][j] != target_grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> test_count;
    while (test_count--) {
        cout << (solve_one() ? "YES" : "NO") << '\n';
    }

    return 0;
}
