/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:19
 * update_at: 2026-07-11 13:23
 */
#include <bits/stdc++.h>
using namespace std;

string answer_grid[3];
string guess_grid[3];
int cnt_answer[26];
int cnt_guess[26];

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

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char a = answer_grid[i][j];
            char b = guess_grid[i][j];

            if (a == b) {
                green++;
            }

            cnt_answer[a - 'A']++;
            cnt_guess[b - 'A']++;
        }
    }

    int total_highlight = 0;
    for (int i = 0; i < 26; i++) {
        total_highlight += min(cnt_answer[i], cnt_guess[i]);
    }

    int yellow = total_highlight - green;

    cout << green << '\n';
    cout << yellow << '\n';

    return 0;
}
