/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:56
 * update_at: 2026-08-14 14:56
 */
#include <iostream>
#include <string>

int main() {
    int q;
    std::cin >> q;
    std::string document;
    std::cin >> document;

    for (int i = 0; i < q; i += 1) {
        int op;
        std::cin >> op;
        if (op == 1) {
            // 追加：把新串接到文档末尾
            std::string text;
            std::cin >> text;
            document += text;
            std::cout << document << '\n';
        } else if (op == 2) {
            // 截取：只保留从第 a 个字符起 b 个字符，下标从 0 开始
            int a, b;
            std::cin >> a >> b;
            document = document.substr(a, b);
            std::cout << document << '\n';
        } else if (op == 3) {
            // 插入：在第 a 个字符前面插入新串
            int a;
            std::string text;
            std::cin >> a >> text;
            document.insert(a, text);
            std::cout << document << '\n';
        } else {
            // 查找：返回第一次出现的位置，找不到返回 -1
            std::string text;
            std::cin >> text;
            std::string::size_type position = document.find(text);
            if (position == std::string::npos) {
                std::cout << -1 << '\n';
            } else {
                std::cout << position << '\n';
            }
        }
    }
    return 0;
}
