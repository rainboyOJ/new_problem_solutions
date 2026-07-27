/**
 * P2789 直线交点数
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

// possible[t] 表示 t 条直线可能产生的交点数集合
// 用布尔数组标记
bool possible[MAXN][MAXN * MAXN / 2 + 5];
int n;

int main() {
    scanf("%d", &n);
    possible[0][0] = true;
    for (int total = 1; total <= n; ++total) {
        // 枚举有 parallel 条直线相互平行（剩余 total-parallel 条不平行）
        for (int parallel = 1; parallel <= total; ++parallel) {
            int add = parallel * (total - parallel); // 平行组与非平行组的交点
            for (int i = 0; i <= (total - parallel) * (total - parallel - 1) / 2; ++i) {
                if (possible[total - parallel][i])
                    possible[total][i + add] = true;
            }
        }
    }
    int ans = 0;
    int max_intersections = n * (n - 1) / 2;
    for (int i = 0; i <= max_intersections; ++i)
        if (possible[n][i]) ++ans;
    printf("%d\n", ans);
    return 0;
}
