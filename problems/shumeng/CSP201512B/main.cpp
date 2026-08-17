/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m;
int board[MAXN][MAXN];    // 棋盘颜色
int removed[MAXN][MAXN];  // removed[i][j]=1 表示该格被消除

// 扫描第 row 行，把连续三个及以上同色的格子标记为消除。
void mark_row(int row) {
    for (int left = 0; left < m;) {
        int right = left + 1;
        while (right < m && board[row][right] == board[row][left]) right++;
        if (right - left >= 3) {
            for (int j = left; j < right; j++) removed[row][j] = 1;
        }
        left = right;
    }
}

// 扫描第 column 列，把连续三个及以上同色的格子标记为消除。
void mark_column(int column) {
    for (int top = 0; top < n;) {
        int bottom = top + 1;
        while (bottom < n && board[bottom][column] == board[top][column]) bottom++;
        if (bottom - top >= 3) {
            for (int i = top; i < bottom; i++) removed[i][column] = 1;
        }
        top = bottom;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> board[i][j];
    }

    // 先全部标记再输出：某格同时满足行、列条件也只消除一次。
    for (int i = 0; i < n; i++) mark_row(i);
    for (int j = 0; j < m; j++) mark_column(j);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j > 0) cout << ' ';
            cout << (removed[i][j] ? 0 : board[i][j]);
        }
        cout << '\n';
    }
    return 0;
}