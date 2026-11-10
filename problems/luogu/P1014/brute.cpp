/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:35
 * update_at: 2026-11-11 00:35
 */

// brute.cpp：蛇形坐标模拟基线
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int r = 1, c = 1;
    // 0: 向右上方走 (r-1, c+1)，1: 向左下方走 (r+1, c-1)
    int dir = 0;

    for (int step = 1; step < n; ++step) {
        if (dir == 0) {
            // 向右上移动
            if (r == 1) {
                c++;
                dir = 1;
            } else {
                r--;
                c++;
            }
        } else {
            // 向左下移动
            if (c == 1) {
                r++;
                dir = 0;
            } else {
                r++;
                c--;
            }
        }
    }

    cout << r << "/" << c << "\n";
    return 0;
}
