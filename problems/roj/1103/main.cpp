/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:15
 * update_at: 2026-10-05 01:15
 */
#include <cstdio>

typedef long long ll;

ll apple[11]; // apple[i] 表示第 i 个苹果到地面的高度（厘米）

int main() {
    ll x = 0; // 陶陶伸手能达到的最大高度
    for (int i = 1; i <= 10; i++) {
        scanf("%lld", &apple[i]);
    }
    scanf("%lld", &x);

    // 板凳有 30 厘米高，先合成阈值；判断用 <=，恰好够到的苹果也算摘到
    ll reach = x + 30;

    ll ans = 0; // 能摘到的苹果数目
    for (int i = 1; i <= 10; i++) {
        if (apple[i] <= reach) {
            ans++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
