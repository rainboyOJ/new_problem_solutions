/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:57
 * update_at: 2026-08-14 14:57
 */
#include <iostream>

// peach(day) 表示第 day 天早上开始时的桃子数
int peach(int day, int n) {
    // 最后一天早上只剩 1 个桃子
    if (day == n) {
        return 1;
    }
    // 当天吃一半再多一个，所以前一天早上 = (当天 + 1) * 2
    return (peach(day + 1, n) + 1) * 2;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << peach(1, n) << '\n';
    return 0;
}
