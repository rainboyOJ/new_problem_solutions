/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:25
 * update_at: 2026-10-06 01:25
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 100005;

int n;
bool is_composite[MAXN]; // is_composite[v] = true 表示 v 是合数（筛掉的数）
int color[MAXN];         // color[i] = 第 i 件珠宝（价值 i+1）的颜色

// 埃氏筛：把 [2, n+1] 里的合数标记出来
void sieve() {
    for (ll p = 2; p * p <= n + 1; p++) {
        if (!is_composite[p]) {
            // 从 p*p 开始划掉，更小的倍数已被更小的质数处理过
            for (ll v = p * p; v <= n + 1; v += p) {
                is_composite[v] = true;
            }
        }
    }
}

int main() {
    scanf("%d", &n);

    sieve();

    // 冲突边只存在于质数与它的倍数之间：质数涂 1，合数涂 2
    // n <= 2 时价值只有 2,3，没有冲突边，全部涂 1，答案为 1
    int k = 1;
    for (int i = 1; i <= n; i++) {
        int v = i + 1;
        if (v >= 4 && is_composite[v]) { // 价值 2,3 是质数，直接涂 1
            color[i] = 2;
            k = 2;
        } else {
            color[i] = 1;
        }
    }

    printf("%d\n", k);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", color[i], i == n ? '\n' : ' ');
    }
    return 0;
}
