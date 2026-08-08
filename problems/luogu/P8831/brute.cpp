#include <bits/stdc++.h>
using namespace std;

const string MONTH_NAME[13] = {
    "", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

const int MONTH_DAY[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

struct Date {
    int day;
    int month;
    int year;
};

string s;
Date target, cur;

bool is_julian_leap(int year) {
    return year % 4 == 0;
}

bool is_gregorian_leap(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    return year % 4 == 0;
}

int get_month_id(const string &month_str) {
    for (int i = 1; i <= 12; i++) {
        if (MONTH_NAME[i] == month_str) {
            return i;
        }
    }
    return 0;
}

void parse_input() {
    cin >> s;

    int pos = 0;
    while (pos < (int) s.size() && isdigit((unsigned char) s[pos])) {
        pos++;
    }

    target.day = stoi(s.substr(0, pos));
    target.month = get_month_id(s.substr(pos, 3));
    target.year = stoi(s.substr(pos + 3));
}

int get_month_day(int year, int month) {
    bool leap = false;

    if (year < 1582) {
        leap = is_julian_leap(year);
    }
    else if (year > 1582) {
        leap = is_gregorian_leap(year);
    }

    return MONTH_DAY[leap][month];
}

bool same_date(const Date &a, const Date &b) {
    return a.day == b.day && a.month == b.month && a.year == b.year;
}

void next_day(Date &x) {
    // 这是题目里最特别的一条规则：1582-10-04 的下一天直接变成 1582-10-15。
    if (x.year == 1582 && x.month == 10 && x.day == 4) {
        x.day = 15;
        return;
    }

    int limit = get_month_day(x.year, x.month);
    if (x.day < limit) {
        x.day++;
        return;
    }

    x.day = 1;
    if (x.month < 12) {
        x.month++;
    }
    else {
        x.month = 1;
        x.year++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    parse_input();

    cur.day = 1;
    cur.month = 1;
    cur.year = 1;

    long long ans = 0;
    while (!same_date(cur, target)) {
        next_day(cur);
        ans++;
    }

    cout << ans << '\n';
    return 0;
}
