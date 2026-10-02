/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:23
 * update_at: 2026-10-01 22:23
 */
// main.cpp：把儒略日编号按换历点分段，分别用儒略历/格里高利历反推日期。
// 核心思路：先算出 1582-10-04（旧历最后一天）的编号，再分两段二分找年份、扫月份。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll START_YEAR = -4712; // 天文年份编号：公元前 4713 年记为 -4712，公元前 1 年记为 0

int month_days_common[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 每月天数（二月按平年）

// 向下取整除法：C++ 对负数除法是截断，这里保证数学意义上的 floor。
ll floor_div(ll a, ll b) {
    if (a >= 0) {
        return a / b;
    }
    return -((-a + b - 1) / b);
}

// 统计 [left, right] 中能被 4 整除的整数个数（含端点），用 floor_div 处理负数。
ll count_multiple_of_4(ll left, ll right) {
    if (left > right) {
        return 0;
    }
    return floor_div(right, 4) - floor_div(left - 1, 4);
}

// 儒略历闰年：年份能被 4 整除就是闰年（含公元前年份）。
bool is_julian_leap(ll year) {
    return year % 4 == 0;
}

// 格里高利历闰年：400 的倍数，或 4 的倍数但不是 100 的倍数。
bool is_gregorian_leap(ll year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

// 返回某年某月的天数；gregorian 决定用哪套闰年规则。
int month_days(ll year, int month, bool gregorian) {
    if (month != 2) {
        return month_days_common[month];
    }
    if (gregorian) {
        return is_gregorian_leap(year) ? 29 : 28;
    }
    return is_julian_leap(year) ? 29 : 28;
}

// 返回某年某月某日是该年的第几天（从 1 开始）。
int day_of_year(ll year, int month, int day, bool gregorian) {
    int result = day;
    for (int m = 1; m < month; m++) {
        result += month_days(year, m, gregorian);
    }
    return result;
}

// 1582-10-04 及以前：从起点 -4712-01-01 到儒略历 date 的天数（0-based）。
ll julian_serial(ll year, int month, int day) {
    ll years = year - START_YEAR;
    ll leaps = count_multiple_of_4(START_YEAR, year - 1);
    return years * 365 + leaps + day_of_year(year, month, day, false) - 1;
}

// 格里高利历中，从 1-01-01 到 date 的天数（0-based），只对正数年份使用。
ll gregorian_ordinal(ll year, int month, int day) {
    ll y = year - 1;
    ll result = y * 365 + y / 4 - y / 100 + y / 400;
    result += day_of_year(year, month, day, true) - 1;
    return result;
}

// 输出日期：year <= 0 时输出「BC」格式，否则输出公元后格式。
void output_date(ll year, ll month, ll day) {
    if (year <= 0) {
        cout << day << ' ' << month << ' ' << 1 - year << " BC\n";
    } else {
        cout << day << ' ' << month << ' ' << year << '\n';
    }
}

// 对单个儒略日 r，先判断落在旧历还是新历，再二分年份、扫月份输出。
void solve_one(ll r) {
    ll last_julian_day = julian_serial(1582, 10, 4);       // 旧历最后一天
    ll first_gregorian_day = last_julian_day + 1;          // 新历第一天的编号
    ll first_gregorian_ordinal = gregorian_ordinal(1582, 10, 15);

    if (r <= last_julian_day) {
        // 旧历段：二分找年份，再从 1 月扫到 12 月定位月份和日。
        ll left = START_YEAR;
        ll right = 1582;
        while (left < right) {
            ll mid = (left + right + 1) / 2;
            if (julian_serial(mid, 1, 1) <= r) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        ll year = left;
        ll remain = r - julian_serial(year, 1, 1); // 当年已过去的天数
        for (int month = 1; month <= 12; month++) {
            int days = month_days(year, month, false);
            if (remain < days) {
                output_date(year, month, remain + 1);
                return;
            }
            remain -= days;
        }
    } else {
        // 新历段：把编号换算成格里高利历连续天数，再二分找年份。
        ll target = first_gregorian_ordinal + (r - first_gregorian_day);

        ll left = 1582;
        ll right = 2000000000LL;
        while (left < right) {
            ll mid = (left + right + 1) / 2;
            if (gregorian_ordinal(mid, 1, 1) <= target) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        ll year = left;
        ll remain = target - gregorian_ordinal(year, 1, 1);
        for (int month = 1; month <= 12; month++) {
            int days = month_days(year, month, true);
            if (remain < days) {
                output_date(year, month, remain + 1);
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
        ll r;
        cin >> r;
        solve_one(r);
    }

    return 0;
}
