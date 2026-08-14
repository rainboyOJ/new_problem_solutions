/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <iostream>

bool is_leap(int year) {
    // 闰年：能被 400 整除，或能被 4 整除但不能被 100 整除
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int main() {
    int start, end;
    std::cin >> start >> end;

    // 区间 [1582, 3000] 内闰年最多约 350 个，预留 400 个位置
    const int max_leap_years = 400;
    int leap_years[max_leap_years];
    int count = 0;

    for (int year = start; year <= end; year += 1) {
        if (is_leap(year)) {
            leap_years[count] = year;
            count += 1;
        }
    }

    // 第一行输出个数，第二行按从小到大输出所有闰年
    std::cout << count << '\n';
    for (int i = 0; i < count; i += 1) {
        std::cout << leap_years[i] << ' ';
    }
    return 0;
}
