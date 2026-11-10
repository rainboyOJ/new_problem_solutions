/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:55
 * update_at: 2026-11-11 01:55
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const int MAXN = 100005;

struct House {
    ll s;
    ll a;

    bool operator<(const House& other) const {
        if (a != other.a) return a > other.a; // 按推销疲劳值 A 降序
        return s > other.s;
    }
};

House h[MAXN];
ll sum_a[MAXN];
ll pre_max_s[MAXN];
ll suf_max_cost[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) cin >> h[i].s;
    for (int i = 1; i <= n; ++i) cin >> h[i].a;

    // 按 A 降序排序
    sort(h + 1, h + n + 1);

    // 预处理前缀和与前缀最大距离
    for (int i = 1; i <= n; ++i) {
        sum_a[i] = sum_a[i - 1] + h[i].a;
        pre_max_s[i] = max(pre_max_s[i - 1], 2 * h[i].s);
    }

    // 预处理后缀 2*S + A 最大值
    suf_max_cost[n + 1] = 0;
    for (int i = n; i >= 1; --i) {
        suf_max_cost[i] = max(suf_max_cost[i + 1], 2 * h[i].s + h[i].a);
    }

    // 对每个 X 输出最大疲劳值
    for (int x = 1; x <= n; ++x) {
        ll plan1 = sum_a[x] + pre_max_s[x];
        ll plan2 = sum_a[x - 1] + suf_max_cost[x];
        cout << max(plan1, plan2) << "\n";
    }

    return 0;
}
