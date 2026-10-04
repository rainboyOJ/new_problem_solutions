/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:04
 * update_at: 2026-10-05 06:04
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

struct Point {
    ll x;
    ll y;
} p[MAXN]; // 输入点集

Point ans[MAXN]; // 极大点结果，按 x 递增存放
int ans_cnt;     // 极大点个数

// 按 x 降序排序，x 相同时按 y 降序
bool cmp(Point a, Point b) {
    if (a.x != b.x) return a.x > b.x;
    return a.y > b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p + 1, p + n + 1, cmp);

    ll max_y = -1; // 坐标非负，-1 作为比所有真实 y 都小的哨兵
    for (int i = 1; i <= n; i++) {
        // 已扫过的点 x 都不小于当前点，只需判断 y 是否大于已扫最大 y
        if (p[i].y > max_y) {
            ans[++ans_cnt] = p[i];
            max_y = p[i].y;
        }
    }

    // 扫描结果 x 递减，反转后得到题目要求的 x 递增顺序
    for (int i = ans_cnt; i >= 1; i--) {
        cout << '(' << ans[i].x << ',' << ans[i].y << ')';
        if (i > 1) cout << ',';
    }
    cout << '\n';

    return 0;
}
