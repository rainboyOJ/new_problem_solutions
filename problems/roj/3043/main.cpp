/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:50
 * update_at: 2026-10-06 15:50
 */

// 3043 超市：反悔贪心（按过期时间升序扫描 + 小根堆）
// 可行性判据：把子集按 d 升序排好后，第 j 小的 d 必须 >= j，
// 所以按 d 扫描时只需保证：处理完所有 d <= D 的商品后，暂定集合大小 <= D。
// 扫描到商品 (p, d) 时，手头所有过期时间 <= d 的商品只能占第 1..d 天，
// 一旦堆大小超过 d，就丢掉利润最小的那件（可用时间相同，留大的不吃亏）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 小根堆：暂定要卖的商品利润；堆内元素之和就是当前最优收益
priority_queue<ll, vector<ll>, greater<ll> > heap;

int main() {
    // 题面允许数据间任意穿插空格与空行，直接按空白流式读入直到 EOF
    ll n;
    while (cin >> n) {
        // 用 pair 的天然排序：first = d（过期时间），second = p（利润）
        vector<pair<ll, ll> > deals; // deals[i] = (d_i, p_i)
        deals.resize(n);
        for (ll i = 0; i < n; ++i) {
            ll p, d;
            cin >> p >> d;
            deals[i] = make_pair(d, p);
        }
        sort(deals.begin(), deals.end()); // 按过期时间 d 升序

        while (!heap.empty()) heap.pop(); // 清空上一组的堆
        for (ll i = 0; i < n; ++i) {
            ll d = deals[i].first;
            ll p = deals[i].second;
            heap.push(p); // 先假设这件商品卖得出去
            ll sz = heap.size();
            if (sz > d) heap.pop(); // 第 1..d 天只有 d 个摊位，退掉最小利润
        }

        ll ans = 0;
        while (!heap.empty()) {
            ans += heap.top();
            heap.pop();
        }
        cout << ans << "\n";
    }
    return 0;
}
