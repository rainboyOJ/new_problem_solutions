/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:51
 * update_at: 2026-10-05 03:51
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 105;

bool is_prime[MAXN]; // is_prime[i] = true 表示 i 是素数

// 埃氏筛，标记 [2, MAXN-1] 范围内的素数
void sieve() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    sieve();
    // 对 6~100 的每个偶数，升序枚举第一个加数，首个两边皆素数的即为最小拆分
    for (int n = 6; n <= 100; n += 2) {
        for (int p = 3; p <= n / 2; p += 2) {
            int q = n - p;
            if (is_prime[p] && is_prime[q]) {
                printf("%d=%d+%d\n", n, p, q);
                break;
            }
        }
    }
    return 0;
}
