/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int leap[2005]; // 存储闰年年份
int cnt;       // 闰年个数

// 判断是否为闰年
bool is_leap(int y) {
    return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int main() {
    int l, r;
    cin >> l >> r;
    for (int y = l; y <= r; y++) {
        if (is_leap(y)) leap[++cnt] = y;
    }
    cout << cnt << "\n";
    for (int i = 1; i <= cnt; i++) cout << leap[i] << " ";
    return 0;
}
