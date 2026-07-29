#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int> &nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1)
            return false;
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int x : nums)
            for (int i = target; i >= x; i--)
                dp[i] = dp[i] || dp[i - x];
        return dp[target];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    cout << Solution().canPartition(a) << '\n';
    return 0;
}
