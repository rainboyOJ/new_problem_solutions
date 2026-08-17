/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:55
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int year, day;
    cin >> year >> day;

    // 每月天数，2 月根据闰年规则改为 29 天。
    int days[13] = {0, 31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) days[2] = 29;

    // 依次扣除每个月，剩余的天数就是该月内的日期。
    int month = 1;
    while (day > days[month]) {
        day -= days[month];
        month++;
    }
    cout << month << '\n' << day << '\n';
    return 0;
}
