/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:38
 * update_at: 2026-10-04 22:38
 */
#include <cstdio>

char ch; // 读入的那个可见字符

int main() {
    scanf("%c", &ch); // %c 直接读入单个字符，题目保证可用
    printf("%d\n", ch); // char 参与运算时整型提升为 int，即其 ASCII 码
    return 0;
}
