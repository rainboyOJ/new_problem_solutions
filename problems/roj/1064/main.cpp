/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 17:07
 * update_at: 2026-10-04 23:57
 */
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

ll n;          // 参与决赛的天数
ll gold;       // 金牌总数
ll silver;     // 银牌总数
ll bronze;     // 铜牌总数

int main() {
    scanf("%lld", &n);
    for (ll i = 0; i < n; i++) {
        ll g, s, b;
        scanf("%lld %lld %lld", &g, &s, &b);
        gold += g;
        silver += s;
        bronze += b;
    }
    printf("%lld %lld %lld %lld\n", gold, silver, bronze, gold + silver + bronze);
    return 0;
}
