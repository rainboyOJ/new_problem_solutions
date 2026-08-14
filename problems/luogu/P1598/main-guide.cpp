/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>
#include <cstring>

const int max_line = 105;

int main() {
    // count[i] 记录大写字母 'A' + i 出现的次数
    int count[26] = {0};

    // 读入 4 行文本，只统计大写字母
    for (int line_index = 0; line_index < 4; line_index += 1) {
        char line[max_line];
        std::cin.getline(line, max_line);
        int length = std::strlen(line);
        for (int i = 0; i < length; i += 1) {
            if (line[i] >= 'A' && line[i] <= 'Z') {
                count[line[i] - 'A'] += 1;
            }
        }
    }

    // 最高的一列决定柱状图的总高度
    int max_height = 0;
    for (int i = 0; i < 26; i += 1) {
        if (count[i] > max_height) {
            max_height = count[i];
        }
    }

    // 从最高层向下逐层输出：达到该层的列打 '*'，否则留空格
    for (int height = max_height; height >= 1; height -= 1) {
        for (int i = 0; i < 26; i += 1) {
            if (count[i] >= height) {
                std::cout << '*';
            } else {
                std::cout << ' ';
            }
            if (i != 25) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    // 最后一行输出 A-Z 作为柱状图的坐标
    for (int i = 0; i < 26; i += 1) {
        std::cout << char('A' + i);
        if (i != 25) {
            std::cout << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}
