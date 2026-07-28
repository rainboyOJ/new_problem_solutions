#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int jump(vector<int>& nums) {
        int n = nums.size(), jumps = 0, curEnd = 0, farthest = 0;
        for (int i = 0; i < n-1; i++) {
            farthest = max(farthest, i + nums[i]);
            if (i == curEnd) { jumps++; curEnd = farthest; }
        }
        return jumps;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    cout << Solution().jump(a) << '\n';
    return 0;
}
