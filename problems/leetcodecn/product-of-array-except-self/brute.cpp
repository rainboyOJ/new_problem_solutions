/**
 * Author by Rainboy
 */
// brute.cpp：每个位置计算除自身外的乘积 O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j) ans[i] *= nums[j];
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto v = Solution().productExceptSelf(a);
    for (int x : v) cout << x << ' ';
    return 0;
}
