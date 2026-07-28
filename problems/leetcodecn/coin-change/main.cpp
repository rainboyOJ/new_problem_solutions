#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount+1); dp[0] = 0;
        for (int i = 1; i <= amount; i++)
            for (int c : coins) if (i >= c) dp[i] = min(dp[i], dp[i-c] + 1);
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, amt; cin >> n >> amt; vector<int> a(n); for (int& x : a) cin >> x;
    cout << Solution().coinChange(a, amt) << '\n';
    return 0;
}
