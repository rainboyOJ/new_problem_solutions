// brute.cpp：小数据暴力解，枚举国内区分到多少廊桥，再直接模拟先到先得。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 105;

struct Flight {
    int arrive;
    int leave;
};

int n, m1, m2;
Flight domestic[MAXM], international_flight[MAXM];

bool cmp_flight(const Flight &a, const Flight &b) {
    return a.arrive < b.arrive;
}

int simulate(Flight flights[], int m, int bridge_count) {
    if (bridge_count == 0) {
        return 0;
    }

    sort(flights + 1, flights + m + 1, cmp_flight);

    priority_queue<int, vector<int>, greater<int> > free_bridge;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > busy;
    for (int i = 1; i <= bridge_count; i++) {
        free_bridge.push(i);
    }

    int answer = 0;
    for (int i = 1; i <= m; i++) {
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
    for (int i = 1; i <= m1; i++) {
        cin >> domestic[i].arrive >> domestic[i].leave;
    }
    for (int i = 1; i <= m2; i++) {
        cin >> international_flight[i].arrive >> international_flight[i].leave;
    }

    int answer = 0;
    for (int domestic_bridge = 0; domestic_bridge <= n; domestic_bridge++) {
        Flight d[MAXM], g[MAXM];
        for (int i = 1; i <= m1; i++) {
            d[i] = domestic[i];
        }
        for (int i = 1; i <= m2; i++) {
            g[i] = international_flight[i];
        }
        int now = simulate(d, m1, domestic_bridge) + simulate(g, m2, n - domestic_bridge);
        answer = max(answer, now);
    }

    cout << answer << '\n';
    return 0;
}
