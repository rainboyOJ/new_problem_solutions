/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:44
 * update_at: 2026-10-05 07:44
 */
// main.cpp：编辑距离，滚动一维数组的前缀 DP。
#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long ll;

const int MAXLEN = 2005;

char a[MAXLEN]; // 字符串 A，下标从 1 开始使用
char b[MAXLEN]; // 字符串 B，下标从 1 开始使用
int dp_prev[MAXLEN]; // dp_prev[j]：上一行（A 的前 i-1 个字符）变成 B 前 j 个字符的最少次数
int dp_cur[MAXLEN];  // dp_cur[j] ：当前行（A 的前 i 个字符）变成 B 前 j 个字符的最少次数

int main() {
    std::cin >> (a + 1) >> (b + 1);
    ll n = strlen(a + 1);
    ll m = strlen(b + 1);

    // 边界：A 为空前缀，B 的前 j 个字符只能逐个插入
    for (ll j = 0; j <= m; j++) {
        dp_prev[j] = j;
    }

    for (ll i = 1; i <= n; i++) {
        dp_cur[0] = i; // 边界：B 为空前缀，A 的前 i 个字符只能逐个删除
        for (ll j = 1; j <= m; j++) {
            if (a[i] == b[j]) {
                // 末位字符相同，直接对上，零代价
                dp_cur[j] = dp_prev[j - 1];
            } else {
                // 三种收尾取最小：删 a[i] / 插 b[j] / 改写 a[i]
                int best = std::min(dp_prev[j], dp_cur[j - 1]);
                best = std::min(best, dp_prev[j - 1]);
                dp_cur[j] = best + 1;
            }
        }
        // 当前行变成下一轮的上一行
        for (ll j = 0; j <= m; j++) {
            dp_prev[j] = dp_cur[j];
        }
    }

    std::cout << dp_prev[m] << std::endl;
    return 0;
}
