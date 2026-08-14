/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:54
 * update_at: 2026-08-14 14:54
 */
/* P1914 小书童-密码：字母平移 n 位，'z' 之后绕回 'a'。 */

#include <iostream>
#include <string>

int main() {
    int shift;             // 平移位数
    std::string password;  // 原始密码
    std::cin >> shift >> password;

    // 逐字符平移：把字母先编号为 0~25，平移后取模实现循环。
    for (int i = 0; i < (int)password.size(); i += 1) {
        int index = password[i] - 'a';          // 当前字母的编号
        index = (index + shift) % 26;           // 平移后取模，超过 'z' 就回到 'a'
        password[i] = 'a' + index;              // 编号转回字母
    }

    std::cout << password << '\n';
    return 0;
}
