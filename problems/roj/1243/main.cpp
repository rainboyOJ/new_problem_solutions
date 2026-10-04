/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:30
 * update_at: 2026-10-05 06:30
 */

// main.cpp：二分答案 + 贪心验证。
// 思路：在 [max(ai), sum(ai)] 上二分最大段和 X，贪心地从左到右尽量把
// 当前段延长，超出 X 就开启新段；统计最少段数，若 <= M 则 X 可行。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, m;
int a[MAXN];

// 判定：在上限 limit 下，能否把序列分成不超过 m 段，使每段和都不超过 limit。
// 贪心：当前段尽量长，超出 limit 就开新段，得到的是最少段数。
bool feasible(int limit) {
    int parts = 1;            // 当前已分出的段数
    int sum = 0;              // 当前段累计和
    for (int i = 1; i <= n; i++) {
        if (a[i] > limit) return false; // 单日就超过上限，必不可行
        if (sum + a[i] <= limit) {
            sum += a[i];      // 还能放当前段
        } else {
            parts++;          // 开启新段
            sum = a[i];
            if (parts > m) return false; // 段数超限，已经不可行
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    int lo = 0, hi = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        lo = max(lo, a[i]);   // 下界：单日最大值（必须能容纳最大的那一天）
        hi += a[i];           // 上界：总和（一整段一定可行）
    }
    // 二分最小的可行上限
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) {
            hi = mid;         // mid 可行，尝试更小
        } else {
            lo = mid + 1;     // mid 不可行，必须更大
        }
    }
    printf("%d\n", lo);
    return 0;
}
