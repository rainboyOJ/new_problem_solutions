/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:25
 * update_at: 2026-07-11 12:27
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 6;
const int MAXC = 30;

int n, a, b;
int total_cell;
char color[MAXN][MAXN];
int choose_star[MAXC]; // choose_star[k]=1 表示第 k 个格子在初始照片中有星星
bool first_photo[MAXN][MAXN];
int best;

void cell_pos(int id, int &r, int &c) {
    r = (id - 1) / n + 1;
    c = (id - 1) % n + 1;
}

bool has_source(int r, int c) {
    return r - b >= 1 && c - a >= 1;
}

bool check_choice() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            first_photo[i][j] = false;
        }
    }

    for (int id = 1; id <= total_cell; id++) {
        int r, c;
        cell_pos(id, r, c);
        if (choose_star[id] == 1) {
            first_photo[r][c] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            bool first = first_photo[i][j];
            bool need_second = false;

            if (color[i][j] == 'W') {
                if (first) {
                    return false;
                }
                need_second = false;
            } else if (color[i][j] == 'G') {
                // 灰色表示前后两张照片恰好一张有星星。
                need_second = !first;
            } else {
                if (!first) {
                    return false;
                }
                need_second = true;
            }

            if (need_second) {
                if (!has_source(i, j)) {
                    return false;
                }
                if (!first_photo[i - b][j - a]) {
                    return false;
                }
            }
        }
    }

    return true;
}

void dfs_choose(int dep, int cnt) {
    if (cnt >= best) {
        return;
    }
    if (dep == total_cell + 1) {
        if (check_choice()) {
            best = cnt;
        }
        return;
    }

    // 这一层选择当前格子初始时有没有星星。
    choose_star[dep] = 0;
    dfs_choose(dep + 1, cnt);

    choose_star[dep] = 1;
    dfs_choose(dep + 1, cnt + 1);
}

int solve_one() {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            color[i][j] = s[j - 1];
        }
    }

    total_cell = n * n;
    best = total_cell + 1;
    dfs_choose(1, 0);

    if (best == total_cell + 1) {
        return -1;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cout << solve_one() << '\n';
    }

    return 0;
}
