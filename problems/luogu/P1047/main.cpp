#include <bits/stdc++.h>
using namespace std;

const int MAXL = 10010;

int l, m;
int d[MAXL]; // 差分数组，统计每个位置被多少个区间覆盖

void solve() {
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        d[u] += 1;
        d[v + 1] -= 1;
    }

    int cover = 0;
    int ans = 0;
    for (int i = 0; i <= l; i++) {
        cover += d[i];
        if (cover == 0) {
            ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> m;
    solve();

    return 0;
}
