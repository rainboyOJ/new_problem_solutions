/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:35
 * update_at: 2026-07-11 13:39
 */
#include <bits/stdc++.h>
using namespace std;

int direction_id(char ch) {
    if (ch == 'E') return 0;
    if (ch == 'N') return 1;
    if (ch == 'W') return 2;
    return 3; // S
}

int turn_value(char from, char to) {
    int a = direction_id(from);
    int b = direction_id(to);
    int diff = (b - a + 4) % 4;

    if (diff == 1) return 1;   // 左转 90 度。
    if (diff == 3) return -1;  // 右转 90 度。
    return 0;                  // 直行。
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int tc = 1; tc <= n; tc++) {
        string s;
        cin >> s;

        int total_turn = 0;
        int len = (int)s.size();

        for (int i = 0; i < len; i++) {
            total_turn += turn_value(s[i], s[(i + 1) % len]);
        }

        if (total_turn > 0) {
            cout << "CCW\n";
        } else {
            cout << "CW\n";
        }
    }

    return 0;
}
