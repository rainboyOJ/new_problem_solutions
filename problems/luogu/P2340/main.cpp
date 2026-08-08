#include <bits/stdc++.h>
using namespace std;

const int OFFSET = 400000;
const int LIMIT = OFFSET * 2;
const int NEG_INF = -1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> iq(n), eq(n);
    for (int i = 0; i < n; i++) {
        cin >> iq[i] >> eq[i];
    }

    // dp[s]：智商和为 s - OFFSET 时，能得到的最大情商和。
    vector<int> dp(LIMIT + 1, NEG_INF);
    dp[OFFSET] = 0;

    int lo = OFFSET, hi = OFFSET;
    for (int i = 0; i < n; i++) {
        int a = iq[i];
        int b = eq[i];

        if (a >= 0) {
            for (int s = min(hi, LIMIT - a); s >= lo; s--) {
                if (dp[s] == NEG_INF) continue;
                dp[s + a] = max(dp[s + a], dp[s] + b);
            }
            hi = min(LIMIT, hi + a);
        } else {
            for (int s = lo; s <= hi; s++) {
                if (dp[s] == NEG_INF) continue;
                dp[s + a] = max(dp[s + a], dp[s] + b);
            }
            lo = max(0, lo + a);
        }
    }

    int answer = 0;
    for (int s = OFFSET; s <= hi; s++) {
        if (dp[s] >= 0) {
            answer = max(answer, dp[s] + s - OFFSET);
        }
    }

    cout << answer << '\n';

    return 0;
}
