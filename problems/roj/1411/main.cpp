/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:15
 * update_at: 2026-10-05 23:15
 */
#include <cstdio>

typedef long long ll;

const int MAXV = 100000; // 值域上限，自身和反序数都不会超过它

// is_composite[i] = true 表示 i 是合数；反序数可能落在区间外，所以筛表必须覆盖全值域
bool is_composite[MAXV + 5];

// 埃氏筛：一次性建出 [0, MAXV] 的素数表，之后判素 O(1) 查表
void sieve() {
    is_composite[0] = is_composite[1] = true;
    for (int i = 2; i * i <= MAXV; ++i)
        if (!is_composite[i])
            for (int j = i * i; j <= MAXV; j += i)
                is_composite[j] = true;
}

int main() {
    sieve();

    int m, n;
    scanf("%d %d", &m, &n);

    bool first = true;      // 控制逗号只在数字之间输出
    bool found = false;     // 区间内是否找到真素数
    for (int i = m; i <= n; ++i) {
        if (is_composite[i]) continue;

        // 求 i 的反序数：逐位取出再拼回去，前导 0 自动消失
        int rev = 0;
        for (int t = i; t > 0; t /= 10)
            rev = rev * 10 + t % 10;

        if (!is_composite[rev]) {
            if (!first) printf(",");
            printf("%d", i);
            first = false;
            found = true;
        }
    }

    if (!found) printf("No");
    printf("\n");
    return 0;
}
