#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);

int n, m;
vector<long long> trip_cost;
long long answer = INF;

// 暴力枚举每一趟运走多少头牛。
// 这个做法只适合小数据，但能直接对应题意。
void dfs(int remain, long long current_cost) {
    if (remain == 0) {
        // 最后一趟不需要返回，所以总成本要少算一次单独返回的时间。
        answer = min(answer, current_cost - m);
        return;
    }

    if (current_cost >= answer + m) {
        return;
    }

    for (int take = 1; take <= remain; take++) {
        dfs(remain - take, current_cost + trip_cost[take]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    trip_cost.assign(n + 1, 0);

    long long prefix = 0;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        prefix += x;
        trip_cost[i] = 2LL * m + prefix;
    }

    dfs(n, 0);
    cout << answer << '\n';

    return 0;
}
