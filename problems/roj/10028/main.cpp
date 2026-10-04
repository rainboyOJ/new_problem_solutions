/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:17
 * update_at: 2026-10-04 22:17
 */
#include <cstdio>

const int LIMIT = 1000000;      // 题面中 N 的上界
const int SIEVE = LIMIT + 100;  // 筛表外扩，保证 N=10^6 时能取到它右侧的素数 1000003

int composite[SIEVE + 1];  // composite[v] = 1 表示 v 是合数
int primes[SIEVE + 1];     // 欧拉筛按从小到大存放素数
int gap[SIEVE + 1];        // gap[v]：合数 v 所处素数间隔的宽度；v 本身是素数时保持 0
int prime_cnt;             // 筛出的素数个数

// 欧拉筛：每个合数只被它的最小素因子划掉一次，整体 O(SIEVE)。
void euler_sieve() {
    for (int v = 2; v <= SIEVE; v++) {
        if (composite[v] == 0) {
            primes[++prime_cnt] = v;
        }
        for (int i = 1; i <= prime_cnt; i++) {
            if (primes[i] > SIEVE / v) {
                break;  // 再乘下去会超出筛表上界，用除法判断避免溢出
            }
            composite[v * primes[i]] = 1;
            if (v % primes[i] == 0) {
                break;  // primes[i] 已是 v 的最小素因子，更大的素因子留给后面的轮次
            }
        }
    }
}

// 把每对相邻素数之间的合数统一登记为这段间隔的宽度。
void fill_gap() {
    for (int i = 2; i <= prime_cnt; i++) {
        int left = primes[i - 1];
        int right = primes[i];
        for (int v = left + 1; v < right; v++) {
            gap[v] = right - left;
        }
    }
}

int main() {
    euler_sieve();
    fill_gap();

    long long n;
    scanf("%lld", &n);
    printf("%d\n", gap[n]);
    return 0;
}
