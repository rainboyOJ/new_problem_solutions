/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:51
 */
#include <bits/stdc++.h>
using namespace std;

// 判断 year 是否为闰年：400 的倍数，或 4 的倍数但不是 100 的倍数。
bool is_leap(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

// 返回 year 年 month 月的天数，2 月需要根据闰年特殊处理。
int days_in_month(int year, int month) {
    int days[13] = {0, 31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap(year)) return 29;
    return days[month];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int month, kth, weekday_needed, first_year, last_year;
    cin >> month >> kth >> weekday_needed >> first_year >> last_year;

    // 1 表示星期一，1850 年 1 月 1 日是星期二。
    // first_weekday_of_year 记录当前年份 1 月 1 日是星期几。
    int first_weekday_of_year = 2;
    for (int year = 1850; year <= last_year; year++) {
        // 从元旦星期顺推目标月 1 日是星期几。
        int first_weekday_of_month = first_weekday_of_year;
        for (int current_month = 1; current_month < month; current_month++) {
            first_weekday_of_month += days_in_month(year, current_month);
            first_weekday_of_month = (first_weekday_of_month - 1) % 7 + 1;
        }

        if (year >= first_year) {
            // 目标月 1 日是 first 时，第一个星期 c 的日期是 1+(c-first+7)%7。
            int first_day = 1 + (weekday_needed - first_weekday_of_month + 7) % 7;
            int answer_day = first_day + 7 * (kth - 1);
            if (answer_day > days_in_month(year, month)) {
                cout << "none\n";
            } else {
                cout << year << '/' << setw(2) << setfill('0') << month << '/'
                     << setw(2) << answer_day << setfill(' ') << '\n';
            }
        }

        // 用当年天数推进到下一年的元旦星期。
        first_weekday_of_year += is_leap(year) ? 366 : 365;
        first_weekday_of_year = (first_weekday_of_year - 1) % 7 + 1;
    }

    return 0;
}
