/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <cmath>
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int chinese;
    int math;
    int english;
    int total;
};

bool is_close(const Student &left, const Student &right) {
    // 三科分差都不超过 5
    if (std::abs(left.chinese - right.chinese) > 5) {
        return false;
    }
    if (std::abs(left.math - right.math) > 5) {
        return false;
    }
    if (std::abs(left.english - right.english) > 5) {
        return false;
    }
    // 总分分差不超过 10
    if (std::abs(left.total - right.total) > 10) {
        return false;
    }
    return true;
}

int main() {
    int student_count;
    std::cin >> student_count;

    const int max_students = 1005;
    Student students[max_students];

    for (int i = 0; i < student_count; i += 1) {
        std::cin >> students[i].name >> students[i].chinese
                 >> students[i].math >> students[i].english;
        students[i].total = students[i].chinese + students[i].math + students[i].english;
    }

    // 输入已按字典序排列，按 i < j 枚举每对学生即可保证输出顺序
    for (int i = 0; i < student_count; i += 1) {
        for (int j = i + 1; j < student_count; j += 1) {
            if (is_close(students[i], students[j])) {
                std::cout << students[i].name << ' ' << students[j].name << '\n';
            }
        }
    }
    return 0;
}
