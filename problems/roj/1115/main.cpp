/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:26
 * update_at: 2026-10-05 02:26
 */
#include <cstdio>

typedef long long ll; // 题目数据统一用 long long

const int MAXX = 10000; // Fmax < 10000，桶下标最大值

int n;
int bucket[MAXX + 5]; // bucket[x] 表示值 x 的出现次数，桶初值为 0，天然覆盖"没出现过输出 0"

int main() {
    scanf("%d", &n);
    ll fmax = 0; // 数组里的最大值，决定统计到哪个数为止
    for (int i = 1; i <= n; ++i) {
        ll x;
        scanf("%lld", &x);
        bucket[x]++;
        if (x > fmax) fmax = x; // 顺手更新最大值
    }
    // 按顺序输出 0..Fmax 每个数的出现次数，没出现的桶保持 0
    for (int i = 0; i <= fmax; ++i)
        printf("%d\n", bucket[i]);
    return 0;
}
