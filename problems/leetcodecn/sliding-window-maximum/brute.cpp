/**
 * Author by Rainboy
 */
// brute.cpp：每个窗口扫描最大值 O(nk)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        int n = nums.size();
        if (n == 0)
            return {};
        vector<int> ans;
        for (int i = 0; i + k <= n; i++)
            ans.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    auto v = Solution().maxSlidingWindow(a, k);
    for (int x : v)
        cout << x << ' ';
    return 0;
}
