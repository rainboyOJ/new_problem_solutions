/**
 * Author by Rainboy
 */
// main.cpp：单调递减队列，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        deque<int> q;
        vector<int> ans;
        for (int i = 0; i < (int)nums.size(); i++) {
            while (!q.empty() && q.front() <= i - k)
                q.pop_front();
            while (!q.empty() && nums[q.back()] <= nums[i])
                q.pop_back();
            q.push_back(i);
            if (i >= k - 1)
                ans.push_back(nums[q.front()]);
        }
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
