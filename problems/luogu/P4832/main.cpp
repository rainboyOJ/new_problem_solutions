#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1000005;
const int NEG_INF = -0x3f3f3f3f;

int n;
int diff_val[MAXM], len_val[MAXM];
int total_abs_diff;
int dp[2 * MAXM + 5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        int cnt_s = 0;
        int cnt_c = 0;
        for (unsigned int j = 0; j < str.size(); j++) {
            if (str[j] == 's') {
                cnt_s++;
            } else if (str[j] == 'c') {
                cnt_c++;
            }
        }
        diff_val[i] = cnt_s - cnt_c;
        len_val[i] = cnt_s + cnt_c;
        total_abs_diff += abs(diff_val[i]);
    }

    int offset = total_abs_diff;
    for (int i = 0; i <= 2 * total_abs_diff; i++) {
        dp[i] = NEG_INF;
    }
    dp[offset] = 0;

    int cur = 0;
    for (int i = 1; i <= n; i++) {
        if (diff_val[i] >= 0) {
            for (int d = cur; d >= -cur; d--) {
                if (dp[d + offset] == NEG_INF) {
                    continue;
                }
                int nd = d + diff_val[i];
                dp[nd + offset] = max(dp[nd + offset], dp[d + offset] + len_val[i]);
            }
        } else {
            for (int d = -cur; d <= cur; d++) {
                if (dp[d + offset] == NEG_INF) {
                    continue;
                }
                int nd = d + diff_val[i];
                dp[nd + offset] = max(dp[nd + offset], dp[d + offset] + len_val[i]);
            }
        }
        cur += abs(diff_val[i]);
    }

    cout << dp[offset] / 2 << '\n';
    return 0;
}
