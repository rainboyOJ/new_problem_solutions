#include <bits/stdc++.h>
using namespace std;

string left_date, right_date;

bool is_leap(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    return year % 4 == 0;
}

int days_in_month(int year, int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12) {
        return 31;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    if (month == 2) {
        if (is_leap(year)) {
            return 29;
        }
        return 28;
    }
    return 0;
}

bool is_valid_date(int year, int month, int day) {
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > days_in_month(year, month)) {
        return false;
    }
    return true;
}

string format_date(int year, int month, int day) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%04d%02d%02d", year, month, day);
    return string(buf);
}

void solve() {
    int start_year = stoi(left_date.substr(0, 4));
    int end_year = stoi(right_date.substr(0, 4));
    int ans = 0;

    for (int year = start_year; year <= end_year; year++) {
        // 回文日期一定形如 abcd dc ba。
        int month = (year % 10) * 10 + (year / 10) % 10;
        int day = (year / 100 % 10) * 10 + year / 1000;

        if (!is_valid_date(year, month, day)) {
            continue;
        }

        string cur = format_date(year, month, day);
        if (cur >= left_date && cur <= right_date) {
            ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> left_date >> right_date;
    solve();

    return 0;
}
