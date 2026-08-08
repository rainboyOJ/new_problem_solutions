// brute.cpp：搜索所有“留在本组/切到下一组”的方案，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const long long INF = (1LL << 60);

int n, m;
int cost_days[MAXN][MAXN];
long long ans = INF;

int next_group(int x) {
    if (x == m) {
        return 1;
    }
    return x + 1;
}

void dfs(int step, int group, long long sum) {
    if (sum >= ans) {
        return;
    }
    if (step == n) {
        ans = min(ans, sum);
        return;
    }

    dfs(step + 1, group, sum + cost_days[group][step + 1]);
    int ng = next_group(group);
    dfs(step + 1, ng, sum + cost_days[ng][step + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost_days[i][j];
        }
    }

    for (int start = 1; start <= m; start++) {
        dfs(1, start, cost_days[start][1]);
    }

    cout << ans << '\n';
    return 0;
}
