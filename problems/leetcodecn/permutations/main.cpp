#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        function<void(int)> dfs = [&](int dep) {
            if (dep == (int)nums.size()) { ans.push_back(nums); return; }
            for (int i = dep; i < (int)nums.size(); i++) {
                swap(nums[dep], nums[i]);
                dfs(dep + 1);
                swap(nums[dep], nums[i]);
            }
        };
        dfs(0);
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    for (auto& v : Solution().permute(a)) { for (int x : v) cout << x << ' '; cout << '\n'; }
    return 0;
}
