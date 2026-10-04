/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-02 15:23
 */
// P9713 「QFOI R1」抱抱
// 关键结论：每一刀都只沿着一个坐标轴切，且切的位置是初始的绝对坐标。
// 于是我们不需要真的维护蛋糕，只要记住：
//   cut[1] = 所有 op=1 的 k 的最大值（切掉 x <= cut[1] 的全部方块）
//   cut[2] = 所有 op=2 的 k 的最大值
//   cut[3] = 所有 op=3 的 k 的最大值
// 剩下的方块恰好是 x > cut[1] 且 y > cut[2] 且 z > cut[3] 的那个小长方体，
// 体积 = (a - cut[1]) * (b - cut[2]) * (c - cut[3])。
// 每次操作只需要用 k 更新一次最大值，再输出体积。
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

ll a, b, c;
int m;

// cut[i] 表示第 i 个维度上“被切掉的部分”能到达的最大坐标，初始为 0
ll cut[4];

void read_data() {
    scanf("%lld %lld %lld %d", &a, &b, &c, &m);
    for (int i = 1; i <= m; ++i) {
        int op;
        ll k;
        scanf("%d %lld", &op, &k);
        // 切的位置只增不减：k 比历史最大值小就说明这一刀已经没有方块可切
        if (k > cut[op]) {
            cut[op] = k;
        }
        // 剩余体积 = 三个方向剩余长度的乘积，最多 1e18，必须用 long long
        ll ans = (a - cut[1]) * (b - cut[2]) * (c - cut[3]);
        printf("%lld\n", ans);
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    read_data();

    return 0;
}
