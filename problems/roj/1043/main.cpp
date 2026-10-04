/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:24
 * update_at: 2026-10-04 23:24
 */
#include <cstdio>

// x 是无符号 32 位数，y 是有符号 32 位数，直接比较会出错：
// C++ 里 unsigned 与 int 比较时 y 会被隐式转成无符号数（如 -1 变成 4294967295），
// 所以必须先把两边统一成 ll 再比。
typedef long long ll;

ll x; // 无符号 32 位范围：0 <= x < 2^32
ll y; // 有符号 32 位范围：-2^31 <= y < 2^31

int main() {
    scanf("%lld %lld", &x, &y);
    if (x > y)
        printf(">\n");
    else if (x == y)
        printf("=\n");
    else
        printf("<\n");
    return 0;
}
