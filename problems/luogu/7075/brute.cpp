// brute.cpp：小数据模拟每天向后走，用来验证换历和公元前输出规则。
#include <bits/stdc++.h>
using namespace std;

struct Date {
    long long year;
    int month;
    int day;
};

int month_days_common[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_julian_leap(long long year) {
    return year % 4 == 0;
}

bool is_gregorian_leap(long long year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

bool is_gregorian_date(const Date &x) {
    if (x.year > 1582) {
        return true;
    }
    if (x.year < 1582) {
        return false;
    }
    if (x.month > 10) {
        return true;
    }
    if (x.month < 10) {
        return false;
    }
    return x.day >= 15;
}

int month_days(const Date &x) {
    if (x.month != 2) {
        return month_days_common[x.month];
    }
    if (is_gregorian_date(x)) {
        return is_gregorian_leap(x.year) ? 29 : 28;
    }
    return is_julian_leap(x.year) ? 29 : 28;
}

void next_day(Date &x) {
    if (x.year == 1582 && x.month == 10 && x.day == 4) {
        x.day = 15;
        return;
    }

    x.day++;
    if (x.day > month_days(x)) {
        x.day = 1;
        x.month++;
        if (x.month > 12) {
            x.month = 1;
            x.year++;
        }
    }
}

void output_date(const Date &x) {
    if (x.year <= 0) {
        cout << x.day << ' ' << x.month << ' ' << 1 - x.year << " BC\n";
    } else {
        cout << x.day << ' ' << x.month << ' ' << x.year << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        long long r;
        cin >> r;

        Date cur;
        cur.year = -4712;
        cur.month = 1;
        cur.day = 1;

        for (long long i = 0; i < r; i++) {
            next_day(cur);
        }
        output_date(cur);
    }

    return 0;
}
