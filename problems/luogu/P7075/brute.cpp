/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:23
 * update_at: 2026-10-01 22:23
 */
// brute.cpp：小数据暴力解，逐日模拟从起点向后走 r 天，用来验证换历和公元前输出规则。
// 只适合 r 不太大的对拍场景（r 数万以内），r 大时会超时。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 日期结构体，year 用天文年份编号（公元前 4713 年 = -4712）。
struct Date {
    ll year;
    int month;
    int day;
};

int month_days_common[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 每月天数（二月按平年）

// 儒略历闰年：年份能被 4 整除就是闰年。
bool is_julian_leap(ll year) {
    return year % 4 == 0;
}

// 格里高利历闰年：400 的倍数，或 4 的倍数但不是 100 的倍数。
bool is_gregorian_leap(ll year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

// 判断日期 x 是否已进入格里高利历（1582-10-15 及以后）。
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

// 返回日期 x 所在月份的天数，自动根据日期选择儒略历或格里高利历闰年规则。
int month_days(const Date &x) {
    if (x.month != 2) {
        return month_days_common[x.month];
    }
    if (is_gregorian_date(x)) {
        return is_gregorian_leap(x.year) ? 29 : 28;
    }
    return is_julian_leap(x.year) ? 29 : 28;
}

// 将日期 x 推进一天，特殊处理 1582-10-04 之后直接跳到 10-15。
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

// 输出日期：year <= 0 时输出「BC」格式，否则输出公元后格式。
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
        ll r;
        cin >> r;

        // 从起点 -4712-01-01 开始，逐日走 r 步。
        Date cur;
        cur.year = -4712;
        cur.month = 1;
        cur.day = 1;

        for (ll i = 0; i < r; i++) {
            next_day(cur);
        }
        output_date(cur);
    }

    return 0;
}
