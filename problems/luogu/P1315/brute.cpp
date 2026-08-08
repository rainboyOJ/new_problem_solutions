#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXM = 25;

int n, m, k;
int d[MAXN];
int remain_add[MAXN];
int latest_time[MAXN];
int from_station[MAXM];
int to_station[MAXM];
int start_time[MAXM];

long long answer = (1LL << 62);

// 按当前每段路减少后的时间，完整模拟一次公交过程。
long long simulate() {
    int arrive_time[MAXN];
    int depart_time[MAXN];

    arrive_time[1] = 0;
    for (int i = 1; i <= n; i++) {
        depart_time[i] = max(arrive_time[i], latest_time[i]);
        if (i < n) {
            int cost = d[i] - remain_add[i];
            arrive_time[i + 1] = depart_time[i] + cost;
        }
    }

    long long total = 0;
    for (int i = 1; i <= m; i++) {
        total += 1LL * arrive_time[to_station[i]] - start_time[i];
    }
    return total;
}

// 枚举每一段路用了多少次加速器。
void dfs(int pos, int left_k) {
    if (pos == n) {
        answer = min(answer, simulate());
        return;
    }

    int limit = min(left_k, d[pos]);
    for (int use = 0; use <= limit; use++) {
        remain_add[pos] = use;
        dfs(pos + 1, left_k - use);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i < n; i++) {
        cin >> d[i];
    }

    for (int i = 1; i <= m; i++) {
        cin >> start_time[i] >> from_station[i] >> to_station[i];
        latest_time[from_station[i]] = max(latest_time[from_station[i]], start_time[i]);
    }

    dfs(1, k);
    cout << answer << '\n';

    return 0;
}
