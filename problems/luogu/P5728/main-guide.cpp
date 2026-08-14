/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>
#include <cmath>

int main() {
    const int max_n = 1005;
    int chinese[max_n] = {};
    int math[max_n] = {};
    int english[max_n] = {};
    int total[max_n] = {};

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i += 1) {
        std::cin >> chinese[i] >> math[i] >> english[i];
        // 提前算好总分，比较时就不用重复相加
        total[i] = chinese[i] + math[i] + english[i];
    }

    int answer = 0;
    // 规定 i < j，保证每对学生只被统计一次
    for (int i = 0; i < n; i += 1) {
        for (int j = i + 1; j < n; j += 1) {
            // 三科分差都不超过 5，且总分分差不超过 10，才是一对对手
            if (std::abs(chinese[i] - chinese[j]) <= 5 &&
                std::abs(math[i] - math[j]) <= 5 &&
                std::abs(english[i] - english[j]) <= 5 &&
                std::abs(total[i] - total[j]) <= 10) {
                answer += 1;
            }
        }
    }

    std::cout << answer;
    return 0;
}
