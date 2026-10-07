/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:35
 * update_at: 2026-10-06 13:35
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20;
const int MAXS = 1 << MAXN; // 点集总数 2^n，n <= 20

int n;
ll a[MAXN][MAXN];        // a[i][j]：点 i 到点 j 的距离
ll f[MAXS][MAXN];        // f[s][j]：走过点集 s（一定含点 0）、当前停在点 j 的最短路径长

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &a[i][j]);

    // 初始化为不可达；边界：只走过起点 {0}、停在起点，代价 0
    memset(f, 0x3f, sizeof(f));
    f[1][0] = 0;

    // s 按二进制数值从小到大枚举：转移的前驱集合 s^(1<<j) < s，保证已算好
    for (int s = 1; s < (1 << n); s++) {
        if (!(s & 1)) continue; // 路径一定从点 0 出发，集合必须含点 0
        for (int j = 0; j < n; j++) {
            if (!((s >> j) & 1)) continue; // j 必须已在集合里
            if (f[s][j] == 0x3f3f3f3f3f3f3f3f) continue;
            // 枚举下一个要走的点 k（当前不在集合里），扩展路径
            for (int k = 0; k < n; k++) {
                if ((s >> k) & 1) continue;
                int ns = s | (1 << k);
                ll cand = f[s][j] + a[j][k];
                if (cand < f[ns][k]) f[ns][k] = cand;
            }
        }
    }

    // 答案：走过全部点、恰好停在终点 n-1
    printf("%lld\n", f[(1 << n) - 1][n - 1]);
    return 0;
}
