/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02 12:49
 * update_at: 2026-10-28 10:00
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 维护当前所有被标记的点，find 时逐个点检查「严格右上」，答案按 x 最小、再 y 最小取。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<pair<int, int>> points; // 当前纸上所有被标记的点

    while (n--) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        if (s[0] == 'a') {
            points.insert({x, y});
        } else if (s[0] == 'r') {
            points.erase({x, y});
        } else {
            // 先找最小的可行 x，再在这个 x 上找最小的可行 y
            int ans_x = -1, ans_y = -1;
            for (auto &p : points) { // set 按 (x, y) 升序，第一个满足条件的点就是答案
                if (p.first > x && p.second > y) {
                    ans_x = p.first;
                    ans_y = p.second;
                    break;
                }
            }
            if (ans_x == -1)
                cout << "-1\n";
            else
                cout << ans_x << ' ' << ans_y << '\n';
        }
    }
    return 0;
}
