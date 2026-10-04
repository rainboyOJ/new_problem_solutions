/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:05
 * update_at: 2026-10-05 00:05
 */
// main.cpp：人口增长，每年增长 0.1%，求 n 年后的人口，保留 4 位小数。
#include <cstdio>

typedef long long ll;

const double GROWTH = 1.001; // 每年的人口是上一年的 1 + 0.1% 倍

int main() {
    ll base, years; // base 为人口基数 x，years 为年数 n
    scanf("%lld %lld", &base, &years);

    double people = base; // 从第 0 年的人口开始，逐年乘上增长倍率
    for (ll i = 1; i <= years; i++) {
        people = people * GROWTH;
    }

    printf("%.4f\n", people);
    return 0;
}
