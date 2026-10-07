/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:42
 * update_at: 2026-10-05 09:42
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll n;
ll b[MAXN]; // b[i] 第 i 个活动的起始时间
ll e[MAXN]; // e[i] 第 i 个活动的结束时间
ll order[MAXN]; // order[i] 第 i 小的活动下标（按 end 升序）

// 比较函数：先按结束时间升序，结束时间相同时按起始时间升序。
bool cmp_by_end(ll x, ll y) {
    if (e[x] != e[y]) return e[x] < e[y];
    return b[x] < b[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> b[i] >> e[i];
        order[i] = i;
    }

    // 按结束时间升序排序：每次优先选结束最早的活动，留出更大后续时间窗。
    sort(order + 1, order + n + 1, cmp_by_end);

    ll ans = 0;
    ll last_end = -1; // 已选活动中最后一个的结束时刻；begin_i >= 0，-1 表示尚未选
    for (ll k = 1; k <= n; k++) {
        ll i = order[k];
        if (b[i] >= last_end) { // 与已选集合不相交，可选
            ans++;
            last_end = e[i];
        }
    }

    cout << ans << "\n";
    return 0;
}
