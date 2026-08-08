// brute.cpp：按天递增枚举区间里的每一个真实日期，直接判断是否回文。
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

void split_date(const string &s, int &year, int &month, int &day) {
    year = stoi(s.substr(0, 4));
    month = stoi(s.substr(4, 2));
    day = stoi(s.substr(6, 2));
}

string format_date(int year, int month, int day) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%04d%02d%02d", year, month, day);
    return string(buf);
}

bool is_palindrome(const string &s) {
    for (int i = 0; i < 4; i++) {
        if (s[i] != s[7 - i]) {
            return false;
        }
    }
    return true;
}

void next_day(int &year, int &month, int &day) {
    day++;
    if (day <= days_in_month(year, month)) {
        return;
    }

    day = 1;
    month++;
    if (month <= 12) {
        return;
    }

    month = 1;
    year++;
}

void solve() {
    int year, month, day;
    int ans = 0;

    split_date(left_date, year, month, day);

    while (true) {
        string cur = format_date(year, month, day);
        if (is_palindrome(cur)) {
            ans++;
        }
        if (cur == right_date) {
            break;
        }
        next_day(year, month, day);
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
