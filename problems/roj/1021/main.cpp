/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:43
 * update_at: 2026-10-04 22:43
 */

#include <cstdio>

typedef long long ll;

int code; // 题目给定的 ASCII 码值，范围很小，用 int 即可避免 %c 的类型转换

int main() {
    scanf("%d", &code);  // 读入码值，题面保证对应可见字符
    printf("%c\n", code); // %c 把码值按字符输出
    return 0;
}
