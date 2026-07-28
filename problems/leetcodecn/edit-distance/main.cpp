#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int minDistance(string a, string b) {
        int m = a.size(), n = b.size();
        vector<int> dp(n+1); iota(dp.begin(), dp.end(), 0);
        for (int i = 1; i <= m; i++) {
            int prev = dp[0]; dp[0] = i;
            for (int j = 1; j <= n; j++) {
                int tmp = dp[j];
                if (a[i-1] == b[j-1]) dp[j] = prev;
                else dp[j] = 1 + min({dp[j], dp[j-1], prev});
                prev = tmp;
            }
        }
        return dp[n];
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string a, b; cin >> a >> b; cout << Solution().minDistance(a,b) << '\n';
    return 0;
}
