/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:25
 * update_at: 2026-10-05 02:25
 */

#include <cstdio>

// 地毯数量上限（题面 n 张，编号 1~n）
const int MAXN = 100005;

int ax[MAXN]; // ax[i] 第 i 张地毯左下角的 x 坐标
int ay[MAXN]; // ay[i] 第 i 张地毯左下角的 y 坐标
int gx[MAXN]; // gx[i] 第 i 张地毯在 x 方向的长度
int gy[MAXN]; // gy[i] 第 i 张地毯在 y 方向的长度

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d %d %d %d", &ax[i], &ay[i], &gx[i], &gy[i]);
    }

    int x, y;
    scanf("%d %d", &x, &y);

    // 后铺的盖在先铺的之上，等价于覆盖该点的地毯中编号最大者获胜。
    // 于是从 n 号倒序枚举，遇到第一张闭矩形覆盖 (x, y) 的地毯就是答案。
    int ans = -1;
    for (int i = n; i >= 1; --i) {
        // 闭矩形判定：边界和顶点上的点也算被覆盖
        if (ax[i] <= x && x <= ax[i] + gx[i] && ay[i] <= y && y <= ay[i] + gy[i]) {
            ans = i;
            break;
        }
    }

    printf("%d\n", ans);
    return 0;
}
