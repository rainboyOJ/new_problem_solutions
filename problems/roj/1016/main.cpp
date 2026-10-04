/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:38
 * update_at: 2026-10-04 22:38
 */

#include <cstdio>

int main() {
    // sizeof 直接问编译器当前平台上该类型占的字节数，无需手写常数
    int int_size = sizeof(int);    // int 的存储空间大小
    int short_size = sizeof(short); // short 的存储空间大小

    // 按题面顺序：先 int 后 short，用一个空格隔开
    printf("%d %d\n", int_size, short_size);
    return 0;
}
