/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

char records[MAXN]; // 保存所有的比赛记录(W/L)
int  len;           // 有效记录长度

// 按 target 分制模拟比赛，输出每局比分
void build_scores(int target) {
    int win = 0, lose = 0; // 当前局 W 和 L 的得分
    for (int i = 0; i < len; i++) {
        if (records[i] == 'W') win++;
        else                   lose++;

        // 当前局结束条件：有人 >= target 且分差 >= 2
        if (max(win, lose) >= target && abs(win - lose) >= 2) {
            cout << win << ":" << lose << "\n";
            win = 0; lose = 0;
        }
    }
    // 输出未完成的最后一局（可能 0:0）
    cout << win << ":" << lose << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char ch;
    while (cin >> ch) {
        if (ch == 'E') break;
        if (ch == 'W' || ch == 'L')
            records[len++] = ch;
    }

    build_scores(11);  // 11 分制
    cout << "\n";
    build_scores(21);  // 21 分制

    return 0;
}
