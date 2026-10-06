/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:32
 * update_at: 2026-10-06 15:32
 */
#include <cstdio>
using namespace std;

typedef long long ll;

int mdays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 平年每月天数，下标即月份

// 闰年判定：4 的倍数且不是 100 的倍数，或 400 的倍数
bool is_leap(ll year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main() {
    ll date1, date2;   // 起止日期（8 位整数）
    ll first_year, last_year;
    ll year;
    ll ans = 0;

    scanf("%lld %lld", &date1, &date2);
    first_year = date1 / 10000; // 起始年份
    last_year = date2 / 10000;  // 终止年份

    for (year = first_year; year <= last_year; year++) {
        // 回文要求后 4 位 = 年份倒序，于是年份一确定，月日就唯一确定
        ll a = year / 1000;       // 年份千位
        ll b = year / 100 % 10;   // 年份百位
        ll c = year / 10 % 10;    // 年份十位
        ll d = year % 10;         // 年份个位
        ll month = d * 10 + c;    // 倒序后的前两位作月份
        ll day = b * 10 + a;      // 倒序后的后两位作日期

        if (month < 1 || month > 12) {
            continue; // 倒序出的月份不合法，该年没有回文日期
        }
        ll days = mdays[month];   // 本月天数
        if (month == 2 && is_leap(year)) {
            days = 29;
        }
        if (day < 1 || day > days) {
            continue; // 该月没有这一天
        }

        ll date = year * 10000 + month * 100 + day; // 拼回 8 位日期
        if (date1 <= date && date <= date2) {       // 只有首尾年份可能越出区间
            ans++;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
