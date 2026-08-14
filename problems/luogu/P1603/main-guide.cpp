/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>
#include <string>
#include <algorithm>

const int dict_size = 27;
const int max_nums = 10;

int main() {
    // 英文数字单词（正规 + 非正规写法）到数值的一一映射
    const std::string words[dict_size] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
        "seventeen", "eighteen", "nineteen", "twenty",
        "a", "both", "another", "first", "second", "third"};
    const int values[dict_size] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        1, 2, 1, 1, 2, 3};

    int nums[max_nums];  // 每个有效单词平方后对 100 取模的值
    int count = 0;

    // 逐词读入，命中单词表才保留该词的平方末两位
    std::string word;
    while (std::cin >> word) {
        for (int i = 0; i < dict_size; i += 1) {
            if (word == words[i]) {
                nums[count] = values[i] * values[i] % 100;
                count += 1;
                break;
            }
        }
    }

    // 每个数都占两位：升序排序后依次拼接，得到的就是最小的排列
    std::sort(nums, nums + count);

    std::string answer = "";
    for (int i = 0; i < count; i += 1) {
        if (nums[i] < 10) {
            answer += '0';
        }
        answer += std::to_string(nums[i]);
    }

    // 去掉开头多余的 0；全部是 0 时说明没有有效数字，输出 0
    int pos = 0;
    while (pos < (int)answer.size() && answer[pos] == '0') {
        pos += 1;
    }
    if (pos == (int)answer.size()) {
        std::cout << 0 << '\n';
    } else {
        std::cout << answer.substr(pos) << '\n';
    }

    return 0;
}
