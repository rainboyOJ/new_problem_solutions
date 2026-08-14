/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int chinese;
    int math;
    int english;
};

int main() {
    int student_count;
    std::cin >> student_count;

    Student best_student;
    int best_total = -1;
    for (int i = 0; i < student_count; i += 1) {
        Student current;
        std::cin >> current.name >> current.chinese >> current.math >> current.english;
        int total = current.chinese + current.math + current.english;
        // 严格大于才更新，总分相同时保留先出现的学生
        if (total > best_total) {
            best_total = total;
            best_student = current;
        }
    }

    std::cout << best_student.name << ' ' << best_student.chinese << ' '
              << best_student.math << ' ' << best_student.english;
    return 0;
}
