/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
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

        // 逐条指令移动：f 上、b 下、l 左、r 右
        for (int i = 0; i < (int)commands.size(); i++) {
            int next_x = x;
            int next_y = y;
            if (commands[i] == 'f') next_y++;
            else if (commands[i] == 'b') next_y--;
            else if (commands[i] == 'l') next_x--;
            else if (commands[i] == 'r') next_x++;
            // 越界则本次指令无效，位置保持不变
            if (1 <= next_x && next_x <= n && 1 <= next_y && next_y <= n) {
                x = next_x;
                y = next_y;
            }
        }
        cout << x << ' ' << y << '\n';
    }

    return 0;
}