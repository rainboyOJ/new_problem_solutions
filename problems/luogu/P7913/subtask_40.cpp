/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 23:21
 * update_at: 2026-10-01 23:21
 */
// subtask_40.cpp：40% 数据 n ≤ 5000, m1+m2 ≤ 5000，用收益前缀和 + 枚举分配。
// 核心思路：对每个区域一次模拟出"分配 i 个廊桥能接多少航班"的前缀和，再枚举分配取最大值。
// 相比 20% 暴力，不再对每个分配重新模拟，而是复用前缀和，时间降到 O(m log m + n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

// 航班：抵达时刻和离开时刻（均 ≤ 10^8，int 足够）。
struct Flight {
    int arrive;
    int leave;
};

ll n, m1, m2;
Flight domestic[MAXN], international_flight[MAXN];
int cnt_domestic[MAXN], cnt_international[MAXN]; // 分配 i 个廊桥时新增接的航班数
int sum_domestic[MAXN], sum_international[MAXN]; // 前缀和：分配 ≤ i 个廊桥共接多少航班

bool cmp_flight(const Flight &a, const Flight &b) {
    return a.arrive < b.arrive;
}

// 模拟一个区域：分配最多 n 个廊桥，用最小可用编号策略，
// 统计每个廊桥编号各接了多少航班，最后做前缀和。
void calc(Flight flights[], ll m, int result[]) {
    sort(flights + 1, flights + m + 1, cmp_flight);

    // 最小堆：空闲廊桥编号（优先用编号最小的）。
    priority_queue<int, vector<int>, greater<int> > free_bridge;
    // 最小堆：(离开时刻, 廊桥编号)，按离开时刻排序。
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > busy;

    ll limit = min(n, m);
    for (ll i = 1; i <= limit; i++) {
        free_bridge.push((int)i);
    }

    for (ll i = 1; i <= m; i++) {
        while (!busy.empty() && busy.top().first < flights[i].arrive) {
            free_bridge.push(busy.top().second);
            busy.pop();
        }

        if (!free_bridge.empty()) {
            int id = free_bridge.top();
            free_bridge.pop();
            result[id]++;
            busy.push(make_pair(flights[i].leave, id));
        }
    }

    // 前缀和：result[i] = 分配 ≤ i 个廊桥共接多少航班。
    for (ll i = 1; i <= n; i++) {
        result[i] += result[i - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m1 >> m2;
    for (ll i = 1; i <= m1; i++) {
        cin >> domestic[i].arrive >> domestic[i].leave;
    }
    for (ll i = 1; i <= m2; i++) {
        cin >> international_flight[i].arrive >> international_flight[i].leave;
    }

    calc(domestic, m1, sum_domestic);
    calc(international_flight, m2, sum_international);

    // 枚举国内分 i 个廊桥，国际分 n-i 个，取最大值。
    int ans = 0;
    for (ll i = 0; i <= n; i++) {
        ans = max(ans, sum_domestic[i] + sum_international[n - i]);
    }
    cout << ans << '\n';

    return 0;
}
