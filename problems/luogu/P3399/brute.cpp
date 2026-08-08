#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据 DFS，枚举每天是休息还是前进。

const int MAXN = 25;
const long long INF = (1LL << 60);

int n, m;
long long d[MAXN];
long long c[MAXN];
long long ans;

void dfs(int day, int city, long long cost) {
    if (day > m) {
        if (city == n) {
            ans = min(ans, cost);
        }
        return;
    }

    // 今天休息。
    dfs(day + 1, city, cost);

    // 今天前进一段。
    if (city < n) {
        dfs(day + 1, city + 1, cost + d[city + 1] * c[day]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> c[i];
    }

    ans = INF;
    dfs(1, 0, 0);

    cout << ans << '\n';
    return 0;
}
