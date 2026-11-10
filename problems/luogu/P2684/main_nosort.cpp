/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 08:11
 * update_at: 2026-11-10 08:40
 *
 * 说明：本文件是「不排序、每步从头扫全部 N 个区间」的对照版本，
 * 用来演示同一个贪心在不排序时的写法与代价。
 * 正确性与 main.cpp 相同，但复杂度退化为 O(N * ans)。
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 25000 + 5;

// 区间结构体：每头奶牛工作的起止时间段
struct Segment {
    ll l;
    ll r;
};

ll n, t;
Segment seg[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> t)) return 0;

    for (ll i = 0; i < n; i++) {
        cin >> seg[i].l >> seg[i].r;
    }

    // 不排序：不依赖区间顺序
    ll cur = 0; // 当前已经连续覆盖到时间点 cur
    ll ans = 0; // 选用的最少奶牛数量

    while (cur < t) {
        ll best = cur; // 记录能覆盖 cur + 1 的所有候选区间中，最远的右端点

        // 每一轮都从头扫全部 N 个区间
        for (ll i = 0; i < n; i++) {
            // 该区间能接上当前缺口 [cur + 1, ...] 才可用
            if (seg[i].l <= cur + 1 && seg[i].r > best) {
                best = seg[i].r;
            }
        }

        // 如果没有任何区间能让 cur 前移，说明出现断档，无法完整覆盖
        if (best == cur) {
            cout << -1 << "\n";
            return 0;
        }

        cur = best;
        ans++;
    }

    cout << ans << "\n";
    return 0;
}
