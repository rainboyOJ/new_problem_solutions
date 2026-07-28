#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> cur;
        function<void(int)> dfs = [&](int i) {
            if (i == (int)nums.size()) { ans.push_back(cur); return; }
            dfs(i+1);
            cur.push_back(nums[i]);
            dfs(i+1);
            cur.pop_back();
        };
        dfs(0);
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    for (auto& v : Solution().subsets(a)) { for (int x : v) cout << x << ' '; cout << '\n'; }
    return 0;
}
