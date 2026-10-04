/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:20
 * update_at: 2026-10-05 00:20
 */
// main.cpp：按递推式生成分数序列的前 n 项并求和，保留 4 位小数。
#include <cstdio>

typedef long long ll;

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }

    ll p = 1;    // 当前项的分母 p_i，初始 p_1 = 1
    ll q = 2;    // 当前项的分子 q_i，初始 q_1 = 2
    double sum = 0.0;
    for (ll i = 1; i <= n; i++) {
        sum += 1.0 * q / p; // 累加第 i 项 q_i / p_i
        ll nextq = q + p;   // 下一项的分子 = 当前项分子 + 当前项分母
        p = q;              // 下一项的分母 = 当前项分子
        q = nextq;
    }
    printf("%.4f\n", sum);
    return 0;
}
