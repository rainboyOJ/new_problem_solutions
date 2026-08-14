/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <iostream>

struct Student {
    int id;
    int academic;
    int quality;
};

bool is_excellent(const Student &student) {
    // 总分必须大于 140
    if (student.academic + student.quality <= 140) {
        return false;
    }
    // 综合分 = academic * 0.7 + quality * 0.3，两边乘 10 变整数比较，避免浮点误差
    return student.academic * 7 + student.quality * 3 >= 800;
}

int main() {
    int student_count;
    std::cin >> student_count;

    for (int i = 0; i < student_count; i += 1) {
        Student student;
        std::cin >> student.id >> student.academic >> student.quality;
        if (is_excellent(student)) {
            std::cout << "Excellent\n";
        } else {
            std::cout << "Not excellent\n";
        }
    }
    return 0;
}
