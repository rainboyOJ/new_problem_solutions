/**
 * Problem: luogu P5023 - [NOIP 2018 提高组] 填数游戏 (Brute Force Verifier)
 * Author: rainboy
 * Date: 2026-11-11 00:50
 * Description: 小规模网格全排列穷举路径判定基准
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, m;
int grid[10][10];

struct Path {
    string dir;
    string val;
};

vector<Path> paths;

void get_paths(int r, int c, string dir_str, string val_str) {
    val_str += to_string(grid[r][c]);
    if (r == n - 1 && c == m - 1) {
        paths.push_back({dir_str, val_str});
        return;
    }
    // 向右走 'R'
    if (c + 1 < m) {
        get_paths(r, c + 1, dir_str + "R", val_str);
    }
    // 向下走 'D'
    if (r + 1 < n) {
        get_paths(r + 1, c, dir_str + "D", val_str);
    }
}

bool check_valid() {
    paths.clear();
    get_paths(0, 0, "", "");

    for (size_t i = 0; i < paths.size(); ++i) {
        for (size_t j = i + 1; j < paths.size(); ++j) {
            const auto &p1 = paths[i];
            const auto &p2 = paths[j];
            if (p1.dir > p2.dir) {
                if (p1.val > p2.val) return false;
            } else if (p1.dir < p2.dir) {
                if (p1.val < p2.val) return false;
            }
        }
    }
    return true;
}

int ans_cnt = 0;

void dfs_grid(int r, int c) {
    if (r == n) {
        if (check_valid()) ans_cnt++;
        return;
    }
    int nr = (c + 1 == m ? r + 1 : r);
    int nc = (c + 1 == m ? 0 : c + 1);

    grid[r][c] = 0;
    dfs_grid(nr, nc);

    grid[r][c] = 1;
    dfs_grid(nr, nc);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    if (n > m) swap(n, m);

    dfs_grid(0, 0);

    cout << ans_cnt << "\n";

    return 0;
}
