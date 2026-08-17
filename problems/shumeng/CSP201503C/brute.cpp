/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:51
 */
// brute.cpp：逐日模拟从 1850 年开始的日历。
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

    int target_month, kth, target_weekday, first_year, last_year;
    cin >> target_month >> kth >> target_weekday >> first_year >> last_year;

    vector<int> answer(last_year - first_year + 1, 0);
    int weekday = 2;
    for (int year = 1850; year <= last_year; year++) {
        int seen = 0;
        for (int month = 1; month <= 12; month++) {
            int limit = days_in_month(year, month);
            for (int day = 1; day <= limit; day++) {
                if (month == target_month && weekday == target_weekday) {
                    seen++;
                    if (seen == kth && year >= first_year) {
                        answer[year - first_year] = day;
                    }
                }
                weekday = weekday % 7 + 1;
            }
        }
    }

    for (int year = first_year; year <= last_year; year++) {
        int day = answer[year - first_year];
        if (day == 0) {
            cout << "none\n";
        } else {
            cout << year << '/' << setw(2) << setfill('0') << target_month << '/'
                 << setw(2) << day << setfill(' ') << '\n';
        }
    }

    return 0;
}
