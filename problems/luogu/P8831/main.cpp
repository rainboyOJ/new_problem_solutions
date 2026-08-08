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

string s;
long long day_num, year_num;
int month_num;

bool is_julian_leap(long long year) {
    return year % 4 == 0;
}

bool is_gregorian_leap(long long year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    return year % 4 == 0;
}

long long count_gregorian_leap(long long year) {
    return year / 4 - year / 100 + year / 400;
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

    day_num = stoll(s.substr(0, pos));
    month_num = get_month_id(s.substr(pos, 3));
    year_num = stoll(s.substr(pos + 3));
}

long long days_before_year(long long year) {
    if (year <= 1) {
        return 0;
    }

    if (year <= 1582) {
        long long last_year = year - 1;
        return last_year * 365 + last_year / 4;
    }

    // 1..1581 按儒略历计算，1582 年实际少了 10 天。
    long long ans = 365LL * 1581 + 1581 / 4;
    ans += 355;

    long long last_year = year - 1;
    ans += (last_year - 1582) * 365;
    ans += count_gregorian_leap(last_year) - count_gregorian_leap(1582);

    return ans;
}

long long days_before_month(long long year, int month) {
    bool leap = false;

    if (year < 1582) {
        leap = is_julian_leap(year);
    }
    else if (year > 1582) {
        leap = is_gregorian_leap(year);
    }

    long long ans = 0;
    for (int i = 1; i < month; i++) {
        ans += MONTH_DAY[leap][i];
    }
    return ans;
}

bool after_cutover(long long year, int month, long long day) {
    if (year != 1582) {
        return false;
    }
    if (month > 10) {
        return true;
    }
    if (month < 10) {
        return false;
    }
    return day >= 15;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    parse_input();

    long long ans = 0;
    ans += days_before_year(year_num);
    ans += days_before_month(year_num, month_num);
    ans += day_num - 1;

    // 只有 1582 年内、并且落在 10 月 15 日及之后的日期，
    // 才需要在当年的统计结果里额外减去不存在的 10 天。
    if (after_cutover(year_num, month_num, day_num)) {
        ans -= 10;
    }

    cout << ans << '\n';
    return 0;
}
