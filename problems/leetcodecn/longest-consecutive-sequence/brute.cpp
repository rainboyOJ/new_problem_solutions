/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 22:01
 * update_at: 2026-07-28 22:01
 */
// brute.cpp：排序后扫描连续段，O(n log n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        if (nums.empty())
            return 0;
        sort(nums.begin(), nums.end());
        int ans = 1, cur = 1;
        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1])
                continue;
            if (nums[i] == nums[i - 1] + 1)
                cur++;
            else
                cur = 1;
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
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    cout << Solution().longestConsecutive(nums) << '\n';
    return 0;
}
