/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 02:09
 */
// brute.cpp：小数据暴力解，逐条指令直接模拟机器人位置。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    while (k--) {
        int x, y;
        string commands;
        cin >> x >> y >> commands;
        for (int i = 0; i < (int)commands.size(); i++) {
            if (commands[i] == 'f' && y < n) y++;
            else if (commands[i] == 'b' && y > 1) y--;
            else if (commands[i] == 'l' && x > 1) x--;
            else if (commands[i] == 'r' && x < n) x++;
        }
        cout << x << ' ' << y << '\n';
    }
    return 0;
}
