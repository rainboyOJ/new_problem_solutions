/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:21
 */
// brute.cpp：小数据暴力解，逐个和之前的局面比较。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> board;
    vector<int> count;
    for (int step = 1; step <= n; step++) {
        string current;
        for (int row = 0; row < 8; row++) {
            string line;
            cin >> line;
            current += line;
        }

        int position = -1;
        for (int i = 0; i < (int)board.size(); i++) {
            if (board[i] == current) {
                position = i;
                break;
            }
        }
        if (position == -1) {
            board.push_back(current);
            count.push_back(1);
            cout << 1 << '\n';
        } else {
            count[position]++;
            cout << count[position] << '\n';
        }
    }

    return 0;
}
