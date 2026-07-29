/**
 * Author by Rainboy
 */
// main.cpp：Kadane 算法，dp[i] = max(a[i], dp[i-1] + a[i])，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        int ans = nums[0], cur = nums[0];
        for (size_t i = 1; i < nums.size(); i++) {
            cur = max(nums[i], cur + nums[i]);
            ans = max(ans, cur);
        }
        return ans;
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
    cout << Solution().maxSubArray(a) << '\n';
    return 0;
}
