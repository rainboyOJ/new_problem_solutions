/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:39
 * update_at: 2026-10-01 22:39
 */
// subtask_20.cpp：20% 数据 n ≤ 100, m1+m2 ≤ 100，枚举国内分几个廊桥再模拟。
// 时间 O(n · m log m)，空间 O(m)。覆盖 20% 档。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 105;

// 航班：抵达时刻和离开时刻。
struct Flight {
    int arrive;
    int leave;
};

ll n, m1, m2;
Flight domestic[MAXM], international_flight[MAXM];

bool cmp_flight(const Flight &a, const Flight &b) {
    return a.arrive < b.arrive;
}

// 模拟一个区域分配 bridge_count 个廊桥，返回能接的航班数。
int simulate(Flight flights[], ll m, ll bridge_count) {
    if (bridge_count == 0) {
        return 0;
    }

    sort(flights + 1, flights + m + 1, cmp_flight);

    priority_queue<int, vector<int>, greater<int> > free_bridge;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > busy;
    for (ll i = 1; i <= bridge_count; i++) {
        free_bridge.push((int)i);
    }

    int answer = 0;
    for (ll i = 1; i <= m; i++) {
        while (!busy.empty() && busy.top().first < flights[i].arrive) {
            free_bridge.push(busy.top().second);
            busy.pop();
        }

        if (!free_bridge.empty()) {
            int id = free_bridge.top();
            free_bridge.pop();
            answer++;
            busy.push(make_pair(flights[i].leave, id));
        }
    }
    return answer;
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

    // 先排序一次，后续 simulate 不会改变顺序。
    sort(domestic + 1, domestic + m1 + 1, cmp_flight);
    sort(international_flight + 1, international_flight + m2 + 1, cmp_flight);

    // 枚举国内分几个廊桥，取两种分配的最大值。
    int answer = 0;
    for (ll domestic_bridge = 0; domestic_bridge <= n; domestic_bridge++) {
        int now = simulate(domestic, m1, domestic_bridge)
                + simulate(international_flight, m2, n - domestic_bridge);
        answer = max(answer, now);
    }

    cout << answer << '\n';
    return 0;
}
