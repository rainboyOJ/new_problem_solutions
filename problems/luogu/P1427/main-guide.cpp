/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 14:53
 * update_at: 2026-08-14 14:53
 */
#include <iostream>

// 每次调用处理一个数：0 是结束标记；否则先递归读下一个数，
// 利用系统调用栈暂存当前数，返回时再输出，从而天然实现逆序
void read_and_print_reversed() {
    int x;
    std::cin >> x;
    if (x == 0) {
        return;
    }
    read_and_print_reversed();
    std::cout << x << ' ';
}

int main() {
    read_and_print_reversed();
    return 0;
}
