/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>
#include <string>

const int max_lines = 2500;

int main() {
    int n;
    std::cin >> n;

    // 最小单位：高 2、宽 4 的三角形，后续每层都由它放大拼成
    std::string pic[max_lines];
    pic[0] = " /\\ ";
    pic[1] = "/__\\";
    int height = 2;

    // 每放大一次：上半部分左右各加 height 个空格（居中），下半部分复制两份
    for (int level = 2; level <= n; level += 1) {
        std::string tmp[max_lines];
        for (int i = 0; i < height; i += 1) {
            tmp[i] = pic[i];
        }
        for (int i = 0; i < height; i += 1) {
            pic[i] = std::string(height, ' ') + tmp[i] + std::string(height, ' ');
        }
        for (int i = 0; i < height; i += 1) {
            pic[i + height] = tmp[i] + tmp[i];
        }
        height *= 2;
    }

    // 去掉每行末尾多余的空格再输出，避免行尾出现空白
    for (int i = 0; i < height; i += 1) {
        int last_char_pos = pic[i].find_last_not_of(' ');
        std::cout << pic[i].substr(0, last_char_pos + 1) << '\n';
    }

    return 0;
}
