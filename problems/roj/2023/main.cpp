/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:46
 * update_at: 2026-10-06 09:46
 */

// main.cpp：三值的排序（USACO sort3）
// 做法：先按 1/2/3 的个数把位置划成三个目标区间，
// 优先做两两直接对换（1 次交换归位 2 个数），
// 剩下的错位必然构成三元环，每个环需要 2 次交换。

#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 1005;

ll n;                 // 序列长度
ll a[MAXN];           // a[i]：第 i 个位置上的数字（1/2/3）
ll cnt[4];            // cnt[v]：数字 v 的总个数
ll miss[4][4];        // miss[i][j]：目标区间 i 的位置上实际放着数字 j 的个数

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);

    // 统计每个数字的总个数，确定三个目标区间的边界
    for (ll i = 1; i <= n; ++i)
        ++cnt[a[i]];

    // 扫描一遍统计错位分布：位置落在哪个目标区间，上面放的却是哪个数字
    ll pos = 0; // 当前位置（1 开始），顺便用它判断属于哪个目标区间
    for (ll i = 1; i <= n; ++i) {
        ++pos;
        ll region; // 该位置排序后应属于的区间编号（1/2/3）
        if (pos <= cnt[1]) region = 1;
        else if (pos <= cnt[1] + cnt[2]) region = 2;
        else region = 3;
        if (region != a[i])
            ++miss[region][a[i]];
    }

    // 第一步：两两直接对换，min(cnt(i,j), cnt(j,i)) 次即可消掉这些对
    ll d12 = std::min(miss[1][2], miss[2][1]);
    ll d13 = std::min(miss[1][3], miss[3][1]);
    ll d23 = std::min(miss[2][3], miss[3][2]);

    // 第二步：剩余错位构成三元环 1->2->3->1（或反向），每个环 2 次交换
    ll remain = (miss[1][2] - d12) + (miss[2][1] - d12);

    printf("%lld\n", d12 + d13 + d23 + remain * 2);
    return 0;
}
