/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 */
// brute.cpp：三重循环枚举所有三元组，O(n³)，去重用 set。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        int n = nums.size();
        set<vector<int>> s;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> t = {nums[i], nums[j], nums[k]};
                        sort(t.begin(), t.end());
                        s.insert(t);
                    }
        return {s.begin(), s.end()};
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
    auto ans = Solution().threeSum(a);
    for (auto &v : ans) {
        for (int x : v)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
