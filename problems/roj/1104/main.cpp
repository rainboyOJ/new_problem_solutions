/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:15
 * update_at: 2026-10-05 01:16
 */
#include <cstdio>

typedef long long ll;

// 十种图书单价，单位：角（原题单价乘以 10 后的整数）
ll price[10] = {289, 327, 456, 780, 350, 862, 278, 430, 560, 650};

int main() {
    ll total = 0; // 总费用，单位：角
    ll c;
    for (int i = 0; i < 10; ++i) {
        scanf("%lld", &c);
        total += price[i] * c; // 对应图书的费用累加
    }
    printf("%.1f\n", total / 10.0); // 角转元，固定输出一位小数
    return 0;
}

