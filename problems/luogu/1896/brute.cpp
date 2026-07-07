/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个格子是否放国王。
#include <bits/stdc++.h>
using namespace std;

int n, k;
int board[10][10];   // board[r][c] = 1 表示 (r,c) 放国王
int choose_cnt;       // 当前已放国王数
long long ans;

// 检查 (r,c) 放国王是否与已放置的冲突（只检查上方和左方）
bool can_place(int r, int c) {
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr, nc = c + dc;
            if (nr >= 1 && nr <= n && nc >= 1 && nc <= n) {
                if (board[nr][nc] == 1) return false;
            }
        }
    }
    return true;
}

// 按行优先顺序递归枚举每个格子
void dfs(int r, int c) {
    if (r > n) {
        // 所有格子处理完
        if (choose_cnt == k) ans++;
        return;
    }

    int nr = r, nc = c + 1;
    if (nc > n) { nr++; nc = 1; }

    // 选择1：不放国王
    board[r][c] = 0;
    dfs(nr, nc);

    // 选择2：放国王
    if (choose_cnt < k && can_place(r, c)) {
        board[r][c] = 1;
        choose_cnt++;
        dfs(nr, nc);
        choose_cnt--;
        board[r][c] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    dfs(1, 1);
    cout << ans << '\n';
    return 0;
}
