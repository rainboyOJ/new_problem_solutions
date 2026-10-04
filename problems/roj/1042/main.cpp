/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:13
 * update_at: 2026-10-04 23:13
 */
// main.cpp：读入一个字符，判断它的 ASCII 值是否为奇数。
#include <iostream>

int main() {
    char ch; // 输入的那个可见字符
    std::cin >> ch;
    int code = ch; // char 参与运算时提升为 int，得到它的 ASCII 值
    if (code % 2 == 1) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
