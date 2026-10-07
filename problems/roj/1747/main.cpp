/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:02
 * update_at: 2026-10-07 21:08
 */
// main.cpp：奶牛排队。求最长的区间 [l, r]，使 a[l] 是区间内严格最小、a[r] 是区间内严格最大。
// 两个单调栈 + 一次二分：st_ge 求"左边最后一个 >= a[r] 的位置"p(r)，
// st_lt 恰好是"右边界能一直延伸到 r 的所有合法左端"，其中下标 > p(r) 的最小者就是 r 的最优左端。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXN = 100005; // n <= 1e5，留一点余量

ll a[MAXN];        // 奶牛身高，值域到 2^32-1，必须用 ll 承载
ll st_ge[MAXN];    // 身高非增的单调栈：栈顶是左边最后一个 >= a[r] 的下标，即 p(r)
ll st_lt[MAXN];    // 身高严格增的单调栈：栈内恰为 { l <= r : a[l] < min(a[l+1..r]) }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) cin >> a[i];

    ll top_ge = 0; // st_ge 的栈顶指针
    ll top_lt = 0; // st_lt 的栈顶指针
    ll ans = 0;

    for (ll r = 1; r <= n; r++) {
        // 求 p(r)：左边最后一个身高 >= a[r] 的位置。它右侧到 r-1 的所有身高都 < a[r]，
        // 所以只要左端 l > p(r)，a[r] 就是 [l, r] 上的严格最大值。
        while (top_ge > 0 && a[st_ge[top_ge]] < a[r]) top_ge--;
        ll p = (top_ge > 0) ? st_ge[top_ge] : 0; // 0 表示左边不存在这样的位置
        st_ge[++top_ge] = r;

        // 维护 st_lt：弹掉所有身高 >= a[r] 的左端（它们的右边界延伸不到 r），
        // 留下的每个 l 都满足 a[l] < a[r] 且 a[l] 是 (l, r] 上的最小值。
        while (top_lt > 0 && a[st_lt[top_lt]] >= a[r]) top_lt--;
        st_lt[++top_lt] = r;

        // st_lt 的下标随栈深递增，二分出第一个下标 > p 的位置：
        // 它同时满足 a[l] < a[r] 与 a[l] < min(a[l+1..r])，下标又最小，所以区间最长。
        ll lo = 1;
        ll hi = top_lt;
        ll pos = top_lt + 1; // 找不到时留在栈外
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            if (st_lt[mid] > p) {
                pos = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        // 只有 l < r 才算真正的区间；pos 落在 r 自己身上时长度为 1，题面不允许，跳过。
        if (pos <= top_lt && st_lt[pos] < r) {
            ll len = r - st_lt[pos] + 1;
            if (len > ans) ans = len;
        }
    }

    cout << ans << '\n';
    return 0;
}
