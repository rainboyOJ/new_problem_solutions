/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:15
 * update_at: 2026-10-05 23:15
 */
#include <cstdio>

typedef long long ll;

int cntA, cntB; // A 类数、B 类数的个数

int main() {
    for (int x = 1; x <= 1000; ++x) {
        int len = 0, t = x;
        while (t) { // 统计 x 的二进制位数
            ++len;
            t >>= 1;
        }
        int ones = 0;
        t = x;
        while (t) { // 统计二进制中 1 的个数
            if (t & 1) ++ones;
            t >>= 1;
        }
        int zeros = len - ones; // 0 的个数 = 总位数 - 1 的个数
        if (ones > zeros) ++cntA;
        else ++cntB;
    }
    printf("%d %d\n", cntA, cntB);
    return 0;
}
