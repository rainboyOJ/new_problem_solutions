/**
 * P1100 高低位交换
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned int n;
    scanf("%u", &n);
    // 低 16 位左移、高 16 位右移，然后合并
    unsigned int ans = (n >> 16) | (n << 16);
    printf("%u\n", ans);
    return 0;
}
