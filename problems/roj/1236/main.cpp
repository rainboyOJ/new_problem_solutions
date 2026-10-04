/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:12
 * update_at: 2026-10-05 06:12
 */
// main.cpp：按左端点排序后单遍扫描，判断区间并集是否为一个闭区间。
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 50005;

typedef long long ll;

struct Interval {
    ll left;
    ll right;
};

ll n;
Interval a[MAXN]; // a[i] 表示第 i 个闭区间 [left, right]

// 按左端点升序排序，保证扫描时左端点单调不减。
bool cmp_interval(const Interval &x, const Interval &y) {
    return x.left < y.left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i].left >> a[i].right;
    }

    sort(a + 1, a + n + 1, cmp_interval);

    ll merged_left = a[1].left; // 最小左端点就是并集的左端点
    ll reach = a[1].right;      // 已并入区间的最大右端点

    for (ll i = 2; i <= n; i++) {
        if (a[i].left > reach) {
            // 左端点越过 reach，中间出现谁都盖不到的空隙，并集被永久劈开。
            cout << "no" << '\n';
            return 0;
        }
        if (a[i].right > reach) {
            reach = a[i].right;
        }
    }

    cout << merged_left << ' ' << reach << '\n';
    return 0;
}
