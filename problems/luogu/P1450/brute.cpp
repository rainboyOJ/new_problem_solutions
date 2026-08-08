#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int coin[5];
int query_count;
int limit_cnt[5];
int target_sum;
i64 ans;

void dfs(int idx, int sum_now) {
    if (idx == 5) {
        if (sum_now == target_sum) {
            ans++;
        }
        return;
    }

    for (int take = 0; take <= limit_cnt[idx]; take++) {
        int ns = sum_now + take * coin[idx];
        if (ns > target_sum) {
            break;
        }
        dfs(idx + 1, ns);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> coin[1] >> coin[2] >> coin[3] >> coin[4] >> query_count;

    while (query_count--) {
        cin >> limit_cnt[1] >> limit_cnt[2] >> limit_cnt[3] >> limit_cnt[4] >> target_sum;
        ans = 0;
        dfs(1, 0);
        cout << ans << '\n';
    }

    return 0;
}
