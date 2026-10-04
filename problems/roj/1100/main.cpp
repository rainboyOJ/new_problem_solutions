/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:08
 * update_at: 2026-10-05 01:08
 */
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

ll days;

int main() {
    scanf("%lld", &days);
    // 前 n 个完整块共占 n(n+1)/2 天，求满足条件的最大 n
    ll n = (ll)((sqrt(8.0 * days + 1.0) - 1.0) / 2.0);
    // 修正浮点误差：若 (n+1)(n+2)/2 <= days，则 n 还可以加 1
    while ((n + 1) * (n + 2) / 2 <= days) n++;
    // 尾块剩余天数
    ll r = days - n * (n + 1) / 2;
    // 完整块贡献 k*k 的和，用平方和公式；尾块每天 n+1 枚
    ll ans = n * (n + 1) * (2 * n + 1) / 6 + r * (n + 1);
    printf("%lld\n", ans);
    return 0;
}
