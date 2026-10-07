/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:41
 * update_at: 2026-10-05 09:41
 */
// main.cpp：区间点覆盖（用最少的点刺穿所有闭区间）的贪心解。
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

struct Interval {
    ll a; // 左端点
    ll b; // 右端点
};

ll n;
Interval seg[MAXN]; // 所有区间，按右端点升序排序后扫描

// 按右端点升序比较，供 sort 使用。
bool cmp_by_right(const Interval &x, const Interval &y) {
    return x.b < y.b;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> seg[i].a >> seg[i].b;
    }
}

void solve() {
    sort(seg + 1, seg + n + 1, cmp_by_right); // 按右端点升序，保证"取右端点"不劣

    ll last = -1; // 已选点中的最大值，-1 表示还没选过点（所有左端点 >= 0）
    ll count = 0;
    for (ll i = 1; i <= n; i++) {
        if (seg[i].a > last) { // 所有已选点都小于左端点，本区间必须新增点
            last = seg[i].b;   // 取右端点能覆盖的后续区间最多
            count++;
        }
    }
    cout << count << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
