/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:40
 * update_at: 2026-10-06 12:41
 */
#include <cstdio>
#include <string>
#include <iostream>

typedef long long ll;

// g[d]：位集，第 e 位为 1 表示数字 d 经任意次变换能变成数字 e（初始含自身，允许 0 次变换）
ll g[10];
// s：数字 n（最多 30 位），按字符串逐位访问；k：规则条数
std::string s;
ll k;

int main() {
    std::cin >> s >> k;
    for (ll d = 0; d < 10; d++) g[d] = (ll)1 << d; // 初始 g[d] 只含 d 自己
    for (ll i = 1; i <= k; i++) {
        ll x, y;
        std::cin >> x >> y;   // 规则 x -> y，加入一条有向边
        g[x] |= (ll)1 << y;
    }
    // Floyd 求传递闭包：若 i 能到 m 且 m 能到 e，则 i 能到 e
    for (ll m = 0; m < 10; m++)
        for (ll i = 0; i < 10; i++)
            if (g[i] >> m & 1) g[i] |= g[m];
    // 每一位数字 d 有 popcount(g[d]) 种取值，各位独立，由乘法原理连乘
    // n 最多 30 位、每位最多 10 种，答案可达 10^30，超出 ll，用 unsigned __int128 输出
    unsigned __int128 ans = 1;
    for (ll i = 0; i < (ll)s.size(); i++) ans *= __builtin_popcountll(g[s[i] - '0']);
    // __int128 无法直接用 cout 输出，转成十进制字符串打印
    std::string out;
    do {
        out += char('0' + (int)(ans % 10));
        ans /= 10;
    } while (ans > 0);
    for (ll i = (ll)out.size() - 1; i >= 0; i--) putchar(out[i]);
    putchar('\n');
    return 0;
}
