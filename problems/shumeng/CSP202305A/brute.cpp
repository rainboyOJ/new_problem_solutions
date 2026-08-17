/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
// brute.cpp：小数据暴力解，逐个和之前出现过的局面比较。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> board;  // 保存不同局面的字符串
vector<int> count_times; // 每个局面已经出现的次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int step = 1; step <= n; step++) {
        // 拼出当前局面
        string current;
        for (int row = 0; row < 8; row++) {
            string line;
            cin >> line;
            current += line;
        }

        // 线性查找之前是否出现过该局面
        int position = -1;
        for (int i = 0; i < (int)board.size(); i++) {
            if (board[i] == current) {
                position = i;
                break;
            }
        }
        if (position == -1) { // 首次出现
            board.push_back(current);
            count_times.push_back(1);
            cout << 1 << '\n';
        } else { // 出现过，次数加一
            count_times[position]++;
            cout << count_times[position] << '\n';
        }
    }

    return 0;
}