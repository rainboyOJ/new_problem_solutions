/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:11
 * update_at: 2026-10-06 13:11
 */
#include <cstdio>
#include <cstdlib>
#include <algorithm>
typedef long long ll;

const int MAXN = 25;   // 网格最大 20x20

int m, n, k;
int a[MAXN][MAXN];     // a[i][j] 表示植株 (i,j) 下的花生数，0 表示没有花生
ll ans = 0;            // 采到的花生总数

// 按"从大到小"依次找下一个最大花生的植株：返回是否找到
bool find_max(int &mr, int &mc, int &mv) {
    mv = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i][j] > mv) {
                mv = a[i][j];
                mr = i;
                mc = j;
            }
    return mv > 0; // 没有剩余花生时返回 false
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);

    ll t = 0;        // 已用时间
    int r = 0, c = 0; // 当前位置，0 表示还在路边

    int mr, mc, mv;
    while (find_max(mr, mc, mv)) {
        // 从当前位置移动到 (mr,mc) 再采摘
        if (r == 0)
            t += mr + 1;                          // 从路边进田：mr 次向下 + 1 次采摘
        else
            t += std::abs(mr - r) + std::abs(mc - c) + 1; // 植株间移动 + 采摘
        // 采完后还要 mr 步才能跳回路边，回不去就停止（后面的花生更少，不采更优）
        if (t + mr > k) break;

        ans += mv;
        a[mr][mc] = 0; // 摘掉这棵植株的花生
        r = mr;
        c = mc;
    }

    printf("%lld\n", ans);
    return 0;
}
