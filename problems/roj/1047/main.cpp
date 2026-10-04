/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:29
 * update_at: 2026-10-04 23:29
 */

#include <cstdio>

typedef long long ll;

// 候选除数按 3、5、7 从小到大给出，沿这个顺序检查，能整除的直接输出，天然"小的在前"
ll divisors[3] = {3, 5, 7};

ll n; // 待判定的整数，可能为负数或 0

int main() {
    scanf("%lld", &n);

    // 用 flag 记录是否至少被一个数整除，决定最后要不要输出 'n'
    bool flag = false;
    for (int i = 0; i < 3; ++i) {
        // 整除判据 n % d == 0：负数输入时余数符号跟随被除数，但"余数为 0"当且仅当整除，依然安全
        if (n % divisors[i] == 0) {
            if (flag) printf(" "); // 不是第一个输出的数，前面补一个空格
            printf("%lld", divisors[i]);
            flag = true;
        }
    }
    // 一个都整除不了
    if (!flag) printf("n");
    printf("\n");
    return 0;
}
