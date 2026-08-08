/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int y, m; // 年份，月份
    cin >> y >> m;
    // 先判断是否闰年（闰年时 is_leap = 1，平年 = 0）
    int is_leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    // 每个月天数，二月 = 28 + is_leap（闰年时 29）
    int days[] = {31, 28 + is_leap, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 月份从 1 开始，数组下标从 0 开始，所以要减 1
    cout << days[m - 1] << endl;
    return 0;
}
