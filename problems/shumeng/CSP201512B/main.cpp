/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:50
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int board[35][35], removed[35][35] = {};
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];
    for (int i = 0; i < n; i++) {
        for (int left = 0; left < m;) {
            int right = left + 1;
            while (right < m && board[i][right] == board[i][left]) right++;
            if (right - left >= 3) for (int j = left; j < right; j++) removed[i][j] = 1;
            left = right;
        }
    }
    for (int j = 0; j < m; j++) {
        for (int top = 0; top < n;) {
            int bottom = top + 1;
            while (bottom < n && board[bottom][j] == board[top][j]) bottom++;
            if (bottom - top >= 3) for (int i = top; i < bottom; i++) removed[i][j] = 1;
            top = bottom;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j) cout << ' ';
            cout << (removed[i][j] ? 0 : board[i][j]);
        }
        cout << '\n';
    }
    return 0;
}
