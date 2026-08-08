#include <bits/stdc++.h>
using namespace std;

int n, limit_w;
int w[25];
int ride_weight[25];
int ans;

void dfs(int idx, int used) {
    if (used >= ans) {
        return;
    }
    if (idx == n + 1) {
        ans = min(ans, used);
        return;
    }

    for (int i = 1; i <= used; i++) {
        if (ride_weight[i] + w[idx] <= limit_w) {
            ride_weight[i] += w[idx];
            dfs(idx + 1, used);
            ride_weight[i] -= w[idx];
        }
    }

    ride_weight[used + 1] = w[idx];
    dfs(idx + 1, used + 1);
    ride_weight[used + 1] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：回溯把每头牛放入已有电梯或新开一趟电梯。
    cin >> n >> limit_w;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    sort(w + 1, w + n + 1, greater<int>());
    memset(ride_weight, 0, sizeof(ride_weight));
    ans = n;
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}
