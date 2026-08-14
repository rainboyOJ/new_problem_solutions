/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:08
 * update_at: 2026-08-14 15:08
 */
#include <iostream>

int main() {
    int per_student, student_count;
    std::cin >> per_student >> student_count;
    // 每人分到的苹果数 × 人数 = 采购总数
    std::cout << per_student * student_count << '\n';
    return 0;
}
