/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>
#include <string>

// 反转"整数部分"：从后往前拼出新串，再去掉新串开头多余的 0
std::string reverse_integer_part(std::string s) {
    std::string result = "";
    int length = (int)s.size();
    for (int i = length - 1; i >= 0; i -= 1) {
        result += s[i];
    }
    // 至少保留一位数字，所以 pos + 1 < size 时才继续跳过
    int pos = 0;
    while (pos + 1 < (int)result.size() && result[pos] == '0') {
        pos += 1;
    }
    return result.substr(pos);
}

// 反转"小数部分"：反转后去掉末尾的 0，但至少要保留一个 '0'
std::string reverse_decimal_part(std::string s) {
    std::string result = "";
    int length = (int)s.size();
    for (int i = length - 1; i >= 0; i -= 1) {
        result += s[i];
    }
    while ((int)result.size() > 1 && result[result.size() - 1] == '0') {
        result.pop_back();
    }
    return result;
}

int main() {
    std::string s;
    std::cin >> s;

    std::size_t dot_pos = s.find('.');
    std::size_t slash_pos = s.find('/');
    std::size_t percent_pos = s.find('%');

    if (dot_pos != std::string::npos) {
        std::string left = s.substr(0, dot_pos);
        std::string right = s.substr(dot_pos + 1);
        std::cout << reverse_integer_part(left) << '.' << reverse_decimal_part(right) << '\n';
    } else if (slash_pos != std::string::npos) {
        // 分数：分子分母分别反转，不带符号，不交换位置
        std::string left = s.substr(0, slash_pos);
        std::string right = s.substr(slash_pos + 1);
        std::cout << reverse_integer_part(left) << '/' << reverse_integer_part(right) << '\n';
    } else if (percent_pos != std::string::npos) {
        // 百分数：只反转数字部分，百分号留在末尾
        std::string number = s.substr(0, percent_pos);
        std::cout << reverse_integer_part(number) << "%\n";
    } else {
        std::cout << reverse_integer_part(s) << '\n';
    }

    return 0;
}
