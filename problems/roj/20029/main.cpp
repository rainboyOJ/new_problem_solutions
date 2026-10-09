/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:00
 * update_at: 2026-10-09 21:45
 */
// 20029《考古发掘区》：二分答案 + 坐标离散化 + 二维差分
// n 可达 5e5 而危险区 T≤100 ⇒ 不能开 n×n 网格。二分边长 L，把每个危险区
// 「反投影」成合法左上角平面上的一个禁放矩形，再判定合法区域是否被全部覆盖。
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXT = 105;           // 危险区数量上界 100
const int MAXC = 2 * MAXT + 4;  // 离散化坐标数上界 = 2 哨兵 + 2*T 矩形端点

struct Point {
    ll x, y;   // 危险区坐标（1-indexed）
};

struct Rect {
    ll x1, x2, y1, y2;  // 禁放矩形 [x1, x2) × [y1, y2)
};

ll n;                   // 遗迹边长
int T;                  // 危险区数量
Point pts[MAXT];        // 危险区坐标
ll xs[MAXC], ys[MAXC];  // 离散化后的 X / Y 坐标
int xn, yn;             // 离散化后的坐标个数
Rect rects[MAXT];       // 每个危险区对应的禁放矩形
int rn;                 // 有效矩形个数
int diff[MAXC][MAXC];   // 二维差分数组
int cov[MAXC][MAXC];    // 前缀和还原后的覆盖次数

// 排序并就地去重，返回去重后的元素个数
int uniq(ll* a, int m) {
    sort(a, a + m);
    int k = 0;
    for (int i = 0; i < m; ++i) {
        if (i == 0 || a[i] != a[i - 1]) a[k++] = a[i];
    }
    return k;
}

// 判定能否放下边长 L 的正方形
bool check(ll L) {
    if (L > n) return false;
    ll lim = n - L + 1;  // 合法左上角取值范围 [1, lim] × [1, lim]

    xn = 0;
    xs[xn++] = 1;          // 搜索域左边界哨兵
    xs[xn++] = n - L + 2;  // 搜索域右边界哨兵（开区间右端）
    yn = 0;
    ys[yn++] = 1;
    ys[yn++] = n - L + 2;

    // 危险区 (x, y) 会让左上角落入 [max(1,x-L+1), min(lim,x)] × [max(1,y-L+1), min(lim,y)]
    rn = 0;
    for (int i = 0; i < T; ++i) {
        ll x1 = max(1LL, pts[i].x - L + 1);
        ll x2 = min(lim, pts[i].x) + 1;
        ll y1 = max(1LL, pts[i].y - L + 1);
        ll y2 = min(lim, pts[i].y) + 1;
        if (x1 < x2 && y1 < y2) {
            rects[rn].x1 = x1;
            rects[rn].x2 = x2;
            rects[rn].y1 = y1;
            rects[rn].y2 = y2;
            ++rn;
            xs[xn++] = x1;
            xs[xn++] = x2;
            ys[yn++] = y1;
            ys[yn++] = y2;
        }
    }

    xn = uniq(xs, xn);
    yn = uniq(ys, yn);

    // 二维差分：矩形区间加一
    for (int i = 0; i < xn; ++i) {
        for (int j = 0; j < yn; ++j) diff[i][j] = 0;
    }
    for (int k = 0; k < rn; ++k) {
        int ix1 = lower_bound(xs, xs + xn, rects[k].x1) - xs;
        int ix2 = lower_bound(xs, xs + xn, rects[k].x2) - xs;
        int iy1 = lower_bound(ys, ys + yn, rects[k].y1) - ys;
        int iy2 = lower_bound(ys, ys + yn, rects[k].y2) - ys;
        diff[ix1][iy1]++;
        diff[ix2][iy1]--;
        diff[ix1][iy2]--;
        diff[ix2][iy2]++;
    }

    // 二维前缀和还原，找一个覆盖次数为 0 且落在合法搜索域内的格子
    for (int i = 0; i < xn - 1; ++i) {
        for (int j = 0; j < yn - 1; ++j) {
            cov[i][j] = diff[i][j];
            if (i > 0) cov[i][j] += cov[i - 1][j];
            if (j > 0) cov[i][j] += cov[i][j - 1];
            if (i > 0 && j > 0) cov[i][j] -= cov[i - 1][j - 1];

            if (cov[i][j] == 0) {
                if (xs[i] <= lim && ys[j] <= lim) return true;
            }
        }
    }
    return false;
}

void solve() {
    if (!(cin >> n >> T)) return;
    for (int i = 0; i < T; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    // 答案关于边长单调 ⇒ 二分；答案为 0 表示任意危险区都放不下
    ll l = 1, r = n, ans = 0;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
