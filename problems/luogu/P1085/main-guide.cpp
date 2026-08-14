/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:18
 * update_at: 2026-08-14 15:18
 */
/* P1085 不高兴的津津：循环 7 天维护总课时最大值，输出最不高兴的那一天。 */

#include <iostream>

int main() {
    int answer_day = 0;  // 0 表示一周里没有任何一天超过 8 小时
    int max_hours = 8;   // 只有总课时严格超过 8 小时才会不高兴

    // day 依次是周一到周日
    for (int day = 1; day <= 7; day += 1) {
        int school_hours, extra_hours;
        std::cin >> school_hours >> extra_hours;
        int total = school_hours + extra_hours;

        // 只在严格更大时更新答案，并列时保留更早的一天
        if (total > max_hours) {
            max_hours = total;
            answer_day = day;
        }
    }

    std::cout << answer_day << '\n';
    return 0;
}
