// main.cpp：把儒略日编号按换历点分段，分别用儒略历/格里高利历反推日期。
#include <bits/stdc++.h>
using namespace std;

const long long START_YEAR = -4712; // 天文年份：公元前 4713 年记为 -4712。

int month_days_common[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

long long floor_div(long long a, long long b) {
    if (a >= 0) {
        return a / b;
    }
    return -((-a + b - 1) / b);
}

long long count_multiple_of_4(long long left, long long right) {
    if (left > right) {
        return 0;
    }
    return floor_div(right, 4) - floor_div(left - 1, 4);
}

bool is_julian_leap(long long year) {
    return year % 4 == 0;
}

bool is_gregorian_leap(long long year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int month_days(long long year, int month, bool gregorian) {
    if (month != 2) {
        return month_days_common[month];
    }
    if (gregorian) {
        return is_gregorian_leap(year) ? 29 : 28;
    }
    return is_julian_leap(year) ? 29 : 28;
}

int day_of_year(long long year, int month, int day, bool gregorian) {
    int result = day;
    for (int m = 1; m < month; m++) {
        result += month_days(year, m, gregorian);
    }
    return result;
}

// 1582-10-04 及以前使用：从起点 -4712-01-01 到儒略历 date 的天数。
long long julian_serial(long long year, int month, int day) {
    long long years = year - START_YEAR;
    long long leaps = count_multiple_of_4(START_YEAR, year - 1);
    return years * 365 + leaps + day_of_year(year, month, day, false) - 1;
}

// 格里高利历中，从 1-01-01 到 date 的天数。
long long gregorian_ordinal(long long year, int month, int day) {
    long long y = year - 1;
    long long result = y * 365 + y / 4 - y / 100 + y / 400;
    result += day_of_year(year, month, day, true) - 1;
    return result;
}

void output_date(long long year, int month, int day) {
    if (year <= 0) {
        cout << day << ' ' << month << ' ' << 1 - year << " BC\n";
    } else {
        cout << day << ' ' << month << ' ' << year << '\n';
    }
}

void solve_one(long long r) {
    long long last_julian_day = julian_serial(1582, 10, 4);
    long long first_gregorian_day = last_julian_day + 1;
    long long first_gregorian_ordinal = gregorian_ordinal(1582, 10, 15);

    if (r <= last_julian_day) {
        long long left = START_YEAR;
        long long right = 1582;
        while (left < right) {
            long long mid = (left + right + 1) / 2;
            if (julian_serial(mid, 1, 1) <= r) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        long long year = left;
        long long remain = r - julian_serial(year, 1, 1);
        for (int month = 1; month <= 12; month++) {
            int days = month_days(year, month, false);
            if (remain < days) {
                output_date(year, month, (int)remain + 1);
                return;
            }
            remain -= days;
        }
    } else {
        long long target = first_gregorian_ordinal + (r - first_gregorian_day);

        long long left = 1582;
        long long right = 2000000000LL;
        while (left < right) {
            long long mid = (left + right + 1) / 2;
            if (gregorian_ordinal(mid, 1, 1) <= target) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        long long year = left;
        long long remain = target - gregorian_ordinal(year, 1, 1);
        for (int month = 1; month <= 12; month++) {
            int days = month_days(year, month, true);
            if (remain < days) {
                output_date(year, month, (int)remain + 1);
                return;
            }
            remain -= days;
        }
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
        solve_one(r);
    }

    return 0;
}
