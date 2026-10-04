/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:21
 * update_at: 2026-10-05 00:21
 */

#include <cstdio>

typedef long long ll;

ll m;          // 每天开始时的药品库存总量
ll n;          // 这一天前来取药的病人数
ll rejectCnt;  // 没有取上药的病人数（答案）

int main() {
    scanf("%lld", &m);
    scanf("%lld", &n);
    for (ll i = 1; i <= n; ++i) {
        ll a;   // 当前病人希望取走的药品数量
        scanf("%lld", &a);
        if (m >= a)  // 库存足够，发药并扣减库存
            m -= a;
        else         // 库存不足，拒绝该病人
            ++rejectCnt;
    }
    printf("%lld\n", rejectCnt);
    return 0;
}
