#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 MOD = 1000000007LL;
const int MAXM = 25;

int T;
int n, m;
int seq_arr[MAXM];
bool used[MAXM];
i64 ans;

// 暴力枚举所有长度为 len 的序列。
void dfs(int pos, int len) {
    if (pos > len) {
        int distinct_cnt = 0;
        memset(used, 0, sizeof(used));

        for (int i = 1; i <= len; i++) {
            if (!used[seq_arr[i]]) {
                used[seq_arr[i]] = true;
                distinct_cnt++;
            }
        }

        ans += distinct_cnt + 1;
        ans %= MOD;
        return;
    }

    for (int x = 1; x <= n; x++) {
        seq_arr[pos] = x;
        dfs(pos + 1, len);
    }
}

i64 solve_one() {
    ans = 0;
    for (int len = 0; len <= m; len++) {
        dfs(1, len);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m;
        cout << solve_one() << '\n';
    }

    return 0;
}
