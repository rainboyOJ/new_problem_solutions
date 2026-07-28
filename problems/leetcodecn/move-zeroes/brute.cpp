/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 */
// brute.cpp：复制非零到新数组，O(n) 空间。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        vector<int> t;
        for (int x : nums) if (x) t.push_back(x);
        fill(t.begin() + t.size(), t.end(), 0);
        // 实际题目要求原地修改
        fill(nums.begin(), nums.end(), 0);
        copy(t.begin(), t.begin() + t.size(), nums.begin());
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    Solution().moveZeroes(a);
    for (int x : a) cout << x << ' ';
    return 0;
}
