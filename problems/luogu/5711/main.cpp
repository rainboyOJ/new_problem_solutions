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
    int year;
    cin >> year;
    // 闰年规则：能被 4 整除但不能被 100 整除，或能被 400 整除
    int is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    cout << is_leap << endl;
    return 0;
}
