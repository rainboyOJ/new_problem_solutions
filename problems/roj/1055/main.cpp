/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:43
 * update_at: 2026-10-04 23:43
 */

#include <cstdio>
typedef long long ll;

ll a; // 题面中的公元年份

int main() {
    scanf("%lld", &a);
    // 公历闰年规则：能被 4 整除才是候选；
    // 但整百年（能被 100 整除）必须再被 400 整除才是闰年（1900 平年、2000 闰年）。
    if (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0))
        printf("Y\n");
    else
        printf("N\n");
    return 0;
}
