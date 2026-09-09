/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:26
 * update_at: 2026-08-28 21:26
 */
// A. Glass：最小外接矩形 + 边界外扩 1。
// 罩子边界上的点不算在罩内，且左上/右下坐标必须是整数：
// 左边界 = minx-1、右边界 = maxx+1，y 方向同理，一遍扫描求四个极值即可。
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
long long minx, miny, maxx, maxy; // x、y 方向的最小/最大值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    minx = miny = INF;
    maxx = maxy = -INF;
    for (int i = 1; i <= n; i++) {
        long long x, y;
        cin >> x >> y;
        // 同时维护 x、y 两个方向的极值，一次扫描完成
        minx = min(minx, x);
        maxx = max(maxx, x);
        miny = min(miny, y);
        maxy = max(maxy, y);
    }
    // 左上角 = (minx-1, miny-1)，右下角 = (maxx+1, maxy+1)
    // 注意官方数据最后一行没有换行，这里第二行也不输出换行
    cout << minx - 1 << ' ' << miny - 1 << '\n';
    cout << maxx + 1 << ' ' << maxy + 1;
    return 0;
}