#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n, k;
int furnace_choose[20];
i64 ans = 0;

void dfs(int pos) {
    if (pos == k + 1) {
        int all_mask = 0;
        for (int i = 1; i <= k; i++) {
            all_mask |= furnace_choose[i];
        }

        if (all_mask == (1 << n) - 1) {
            ans++;
        }
        return;
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        furnace_choose[pos] = mask;
        dfs(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    dfs(1);
    cout << ans % 998244353 << '\n';
    return 0;
}
