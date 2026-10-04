/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:06
 * update_at: 2026-10-04 22:09
 */
#include <cstdio>

typedef long long ll;

ll a, b, c; // 读入的三个整数

int main() {
    // 一行三个 32 位有符号整数，按空格切分后取中间那个
    scanf("%lld %lld %lld", &a, &b, &c);
    printf("%lld\n", b);
    return 0;
}