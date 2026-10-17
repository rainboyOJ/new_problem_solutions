/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-17 23:02
 * update_at: 2026-10-17 23:02
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按定义做：把出现过的矩形全部存下来，每来一个查询就扫一遍所有矩形，
// 判断 l <= x < r && d <= y < u，命中就累加权值 w。
// 复杂度 O(Q * N)，只适合小数据（N、Q 几百以内）。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 100005;

struct Rect {
    ll l, d, r, u, w; // 矩形 [l,r) x [d,u)，权值 w
};

Rect rect[maxn]; // 出现过的全部矩形（初始的 + 后来加的）
int rect_cnt;    // 当前矩形个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        rect_cnt++;
        cin >> rect[rect_cnt].l >> rect[rect_cnt].d >> rect[rect_cnt].r >> rect[rect_cnt].u >> rect[rect_cnt].w;
    }

    for (int i = 1; i <= q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            rect_cnt++;
            cin >> rect[rect_cnt].l >> rect[rect_cnt].d >> rect[rect_cnt].r >> rect[rect_cnt].u >> rect[rect_cnt].w;
        } else {
            ll x, y;
            cin >> x >> y;
            ll sum = 0;
            for (int k = 1; k <= rect_cnt; k++) {
                // 半开区间：左、下边界含，右、上边界不含
                if (rect[k].l <= x && x < rect[k].r && rect[k].d <= y && y < rect[k].u) sum += rect[k].w;
            }
            printf("%lld\n", sum);
        }
    }
    return 0;
}
