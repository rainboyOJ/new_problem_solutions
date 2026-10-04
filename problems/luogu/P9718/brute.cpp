/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 12:31
 * update_at: 2026-10-03 12:31
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
//
// 直接从小到大枚举 y = 1, 2, 3, ...，
// 用竖式加法逐位模拟 x + y，统计 a[i] + b[i] + c 达到 10 的次数，
// 第一次恰好等于 k 的 y 就是答案。
// 注意：最高位之外的悬挂进位不算「进位」，所以只在两数都处理完之前统计。
// 因为答案可能很大，枚举上限取 LIMIT；配套的 gen.py 只生成答案远小于 LIMIT 的小数据。
#include <bits/stdc++.h>
using namespace std;

const long long LIMIT = 2000000;   // 枚举上限，保证对拍数据足够小

// 统计 x + y 竖式加法的进位次数
int count_carry(long long x, long long y) {
    int c = 0;        // 当前进位
    int cnt = 0;      // 已经发生的进位次数
    while (x > 0 || y > 0) {
        int s = (int)(x % 10) + (int)(y % 10) + c;
        if (s >= 10) {
            c = 1;
            cnt++;
        } else {
            c = 0;
        }
        x /= 10;
        y /= 10;
    }
    // 循环结束后剩下的进位是最高位的悬挂进位，题目不计入
    return cnt;
}

void solve_one(long long x, int k) {
    for (long long y = 1; y <= LIMIT; y++) {
        if (count_carry(x, y) == k) {
            printf("%lld\n", y);
            return;
        }
    }
    puts("-1");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long x;
        int k;
        scanf("%lld %d", &x, &k);
        solve_one(x, k);
    }
    return 0;
}
