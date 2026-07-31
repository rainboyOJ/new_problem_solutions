/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:53
 */
#include <bits/stdc++.h>
using namespace std;

bool is_leap(int year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

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
    int first_weekday_of_year = 2;
    for (int year = 1850; year <= last_year; year++) {
        int first_weekday_of_month = first_weekday_of_year;
        for (int current_month = 1; current_month < month; current_month++) {
            first_weekday_of_month += days_in_month(year, current_month);
            first_weekday_of_month = (first_weekday_of_month - 1) % 7 + 1;
        }

        if (year >= first_year) {
            int first_day = 1 + (weekday_needed - first_weekday_of_month + 7) % 7;
            int answer_day = first_day + 7 * (kth - 1);
            if (answer_day > days_in_month(year, month)) {
                cout << "none\n";
            } else {
                cout << year << '/' << setw(2) << setfill('0') << month << '/'
                     << setw(2) << answer_day << setfill(' ') << '\n';
            }
        }

        first_weekday_of_year += is_leap(year) ? 366 : 365;
        first_weekday_of_year = (first_weekday_of_year - 1) % 7 + 1;
    }

    return 0;
}
