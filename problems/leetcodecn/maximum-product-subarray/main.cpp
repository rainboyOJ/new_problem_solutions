#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0], mx = nums[0], mn = nums[0];
        for (int i = 1; i < (int)nums.size(); i++) {
            int x = nums[i];
            int a = max({x, mx*x, mn*x});
            int b = min({x, mx*x, mn*x});
            mx = a; mn = b;
            ans = max(ans, mx);
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    cout << Solution().maxProduct(a) << '\n';
    return 0;
}
