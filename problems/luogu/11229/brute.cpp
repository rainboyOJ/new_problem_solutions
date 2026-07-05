// brute.cpp：小数据 DP，保存每个火柴数能拼出的最小字符串。
#include <bits/stdc++.h>
using namespace std;

int cost_digit[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

bool better(const string &a, const string &b) {
    if (a.empty()) {
        return false;
    }
    if (b.empty()) {
        return true;
    }
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        vector<string> dp(n + 1, "");
        for (int d = 1; d <= 9; d++) {
            if (cost_digit[d] <= n) {
                string s = "";
                s += char('0' + d);
                if (better(s, dp[cost_digit[d]])) {
                    dp[cost_digit[d]] = s;
                }
            }
        }

        for (int sum = 0; sum <= n; sum++) {
            if (dp[sum].empty()) {
                continue;
            }
            for (int d = 0; d <= 9; d++) {
                int next_sum = sum + cost_digit[d];
                if (next_sum > n) {
                    continue;
                }
                string s = dp[sum] + char('0' + d);
                if (better(s, dp[next_sum])) {
                    dp[next_sum] = s;
                }
            }
        }

        if (dp[n].empty()) {
            cout << -1 << '\n';
        } else {
            cout << dp[n] << '\n';
        }
    }

    return 0;
}
