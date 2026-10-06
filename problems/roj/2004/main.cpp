/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:17
 * update_at: 2026-10-06 09:17
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MAXN = 5005; // 农民数量上限

ll n;
struct Span {
    ll s; // 开始时刻
    ll e; // 结束时刻
} a[MAXN]; // 所有挤奶区间

// 按左端点升序排序
bool cmp_span(const Span &x, const Span &y) {
    return x.s < y.s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i].s >> a[i].e;
    }

    sort(a + 1, a + n + 1, cmp_span);

    // 合并成极大连通块，同时统计答案
    ll block_l = a[1].s;   // 当前块左端点
    ll block_r = a[1].e;   // 当前块右端点
    ll milked = 0;         // 最长有奶时长
    ll idle = 0;           // 最长空档时长

    for (ll i = 2; i <= n; i++) {
        if (a[i].s <= block_r) { // 重叠或首尾相接，属于同一块
            if (a[i].e > block_r) {
                block_r = a[i].e;
            }
        } else { // 断开，结算当前块并开启新块
            milked = max(milked, block_r - block_l);
            idle = max(idle, a[i].s - block_r);
            block_l = a[i].s;
            block_r = a[i].e;
        }
    }
    milked = max(milked, block_r - block_l); // 最后一块也要参与

    cout << milked << " " << idle << "\n";
    return 0;
}
