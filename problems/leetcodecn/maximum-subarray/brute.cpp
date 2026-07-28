/**
 * Author by Rainboy
 */
// brute.cpp：枚举所有子数组 O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size(), ans = INT_MIN;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += nums[j];
                ans = max(ans, sum);
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << Solution().maxSubArray(a) << '\n';
    return 0;
}
