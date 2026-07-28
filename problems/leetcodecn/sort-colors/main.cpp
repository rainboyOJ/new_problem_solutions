#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    void sortColors(vector<int>& nums) {
        int l = 0, m = 0, r = nums.size() - 1;
        while (m <= r) {
            if (nums[m] == 0) swap(nums[l++], nums[m++]);
            else if (nums[m] == 1) m++;
            else swap(nums[m], nums[r--]);
        }
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    Solution().sortColors(a); for (int x : a) cout << x << ' ';
    return 0;
}
