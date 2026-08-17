/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:55
 */
// brute.cpp：从 1 月 1 日开始逐日推进。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int year, target_day;
    cin >> year >> target_day;

    // 从 1 月 1 日开始逐日推进，走满 target_day 天。
    int month = 1, day = 1;
    bool leap = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    int days[13] = {0, 31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31};
    if (leap) days[2] = 29;
    for (int count = 1; count < target_day; count++) {
        day++;
        if (day > days[month]) {
            month++;
            day = 1;
        }
    }
    cout << month << '\n' << day << '\n';
    return 0;
}
