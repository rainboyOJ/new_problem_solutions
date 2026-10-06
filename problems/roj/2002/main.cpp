/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:05
 * update_at: 2026-10-06 09:05
 */
#include <iostream>
using namespace std;

typedef long long ll;

int mdays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 判断闰年：4 的倍数且非 100 的倍数，或 400 的倍数
bool is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 返回 year 年 month 月的总天数（month 为 1~12）
int days_of_month(int year, int month) {
    if (month == 2 && is_leap(year)) return 29;
    return mdays[month];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // cnt[w] 表示 13 号落在星期 w 的次数
    // w 定义：0=星期六,1=星期日,2=星期一,3=星期二,4=星期三,5=星期四,6=星期五
    int cnt[7] = {0};

    // 1900-01-01 是星期一，到 1900-01-13 相差 12 天，(2+12)%7=0，即星期六
    int weekday = 0;

    for (int year = 1900; year <= 1900 + n - 1; ++year) {
        for (int month = 1; month <= 12; ++month) {
            cnt[weekday]++;
            weekday = (weekday + days_of_month(year, month)) % 7;
        }
    }

    for (int i = 0; i < 7; ++i) {
        if (i) cout << ' ';
        cout << cnt[i];
    }
    cout << '\n';
    return 0;
}
