/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

int n;
map<string, int> appeared; // 局面字符串 -> 已经出现的次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int step = 1; step <= n; step++) {
        // 每 8 行拼成一个长度为 64 的字符串表示当前局面
        string board;
        for (int row = 0; row < 8; row++) {
            string line;
            cin >> line;
            board += line;
        }
        // 先累计本次出现，再输出次数
        appeared[board]++;
        cout << appeared[board] << '\n';
    }

    return 0;
}