/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:44
 * update_at: 2026-10-05 12:44
 */
// main.cpp：统计当月短信资费，每次发送占 ceil(字数/70) 条，每条 0.1 元。
#include <cstdio>

typedef long long ll;

int main() {
    ll n; // 当月发送短信的总次数
    if (scanf("%lld", &n) != 1) {
        return 0;
    }

    ll total = 0; // 总条数，整数累加避免浮点误差
    for (ll i = 1; i <= n; i++) {
        ll length; // 本次发送的字数
        scanf("%lld", &length);
        // 向上取整写成 (length + 69) / 70 的整数除法，正好等于需要几条短信
        total += (length + 69) / 70;
    }

    // 每条 0.1 元，等价于总条数除以 10，保留一位小数输出
    printf("%.1f\n", total / 10.0);
    return 0;
}
