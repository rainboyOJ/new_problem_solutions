/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 22:31
 * update_at: 2026-10-05 04:33
 */
#include <cstdio>
#include <algorithm>

typedef long long ll;

ll a[15]; // 输入的10个整数

// 按题意排序：奇数在前且降序，偶数在后且升序
bool cmp(ll x, ll y) {
    int ox = x & 1; // x 的奇偶性，1 为奇数
    int oy = y & 1; // y 的奇偶性
    if (ox != oy) return ox > oy; // 奇数排在偶数前面
    if (ox == 1) return x > y; // 同为奇数，降序
    return x < y; // 同为偶数，升序
}

int main() {
    for (int i = 0; i < 10; i++) {
        scanf("%lld", &a[i]);
    }
    std::sort(a, a + 10, cmp); // 按自定义奇偶规则排序
    for (int i = 0; i < 10; i++) {
        if (i) printf(" ");
        printf("%lld", a[i]);
    }
    printf("\n");
    return 0;
}
