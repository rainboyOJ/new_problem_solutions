// main.cpp：用最小可用廊桥编号模拟每个区域，统计分配 i 个廊桥能接多少航班。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Flight {
    int arrive;
    int leave;
};

int n, m1, m2;
Flight domestic[MAXN], international_flight[MAXN];
int cnt_domestic[MAXN], cnt_international[MAXN];
int sum_domestic[MAXN], sum_international[MAXN];

bool cmp_flight(const Flight &a, const Flight &b) {
    return a.arrive < b.arrive;
}

void calc(Flight flights[], int m, int result[]) {
    sort(flights + 1, flights + m + 1, cmp_flight);

    priority_queue<int, vector<int>, greater<int> > free_bridge;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > busy;

    int limit = min(n, m);
    for (int i = 1; i <= limit; i++) {
        free_bridge.push(i);
    }

    for (int i = 1; i <= m; i++) {
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

    for (int i = 1; i <= n; i++) {
        result[i] += result[i - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++) {
        cin >> domestic[i].arrive >> domestic[i].leave;
    }
    for (int i = 1; i <= m2; i++) {
        cin >> international_flight[i].arrive >> international_flight[i].leave;
    }

    calc(domestic, m1, sum_domestic);
    calc(international_flight, m2, sum_international);

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, sum_domestic[i] + sum_international[n - i]);
    }
    cout << ans << '\n';

    return 0;
}
