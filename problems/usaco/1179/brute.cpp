/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:19
 * update_at: 2026-07-11 13:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string answer_grid[3];
string guess_grid[3];
bool answer_used[3][3];
bool guess_green[3][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 3; i++) {
        cin >> answer_grid[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> guess_grid[i];
    }

    int green = 0;
    int yellow = 0;

    // 先处理位置完全相同的绿色格子。
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (answer_grid[i][j] == guess_grid[i][j]) {
                green++;
                answer_used[i][j] = true;
                guess_green[i][j] = true;
            }
        }
    }

    // 再给每个没有变绿的猜测格，找一个还没使用过的同字母答案格。
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (guess_green[i][j]) {
                continue;
            }

            bool found = false;
            for (int x = 0; x < 3 && !found; x++) {
                for (int y = 0; y < 3 && !found; y++) {
                    if (!answer_used[x][y] && answer_grid[x][y] == guess_grid[i][j]) {
                        answer_used[x][y] = true;
                        yellow++;
                        found = true;
                    }
                }
            }
        }
    }

    cout << green << '\n';
    cout << yellow << '\n';

    return 0;
}
