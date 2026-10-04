/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:16
 * update_at: 2026-10-04 22:16
 */
#include <cstdio>
using namespace std;

typedef long long ll;

ll a, b, c; // 读入的三个整数

int main() {
    // 读入三个整数
    scanf("%lld %lld %lld", &a, &b, &c);
    // 每个数按最小宽度 8 右对齐输出，数之间用一个空格分隔
    printf("%8lld %8lld %8lld\n", a, b, c);
    return 0;
}
