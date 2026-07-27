/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

// 每个数字 0~9 的 5 行 3 列点阵模板
char pat[10][5][4] = {
    {"XXX", "X.X", "X.X", "X.X", "XXX"}, // 0
    {"..X", "..X", "..X", "..X", "..X"}, // 1
    {"XXX", "..X", "XXX", "X..", "XXX"}, // 2
    {"XXX", "..X", "XXX", "..X", "XXX"}, // 3
    {"X.X", "X.X", "XXX", "..X", "..X"}, // 4
    {"XXX", "X..", "XXX", "..X", "XXX"}, // 5
    {"XXX", "X..", "XXX", "X.X", "XXX"}, // 6
    {"XXX", "..X", "..X", "..X", "..X"}, // 7
    {"XXX", "X.X", "XXX", "X.X", "XXX"}, // 8
    {"XXX", "X.X", "XXX", "..X", "XXX"}  // 9
};

int n;
char s[1005];

int main() {
    cin >> n >> s;
    // 按行输出，每行依次输出每个数字的对应行，用点隔开
    for (int r = 0; r < 5; r++) {
        for (int i = 0; i < n; i++) {
            int d = s[i] - '0';
            cout << pat[d][r];
            if (i != n - 1) cout << "."; // 数字之间插一列点
        }
        cout << "\n";
    }
    return 0;
}
