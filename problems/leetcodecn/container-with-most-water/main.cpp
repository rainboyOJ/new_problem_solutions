/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 */
// main.cpp：双指针，每次移动较矮一侧，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
        int l = 0, r = height.size() - 1, ans = 0;
        while (l < r) {
            int h = min(height[l], height[r]);
            ans = max(ans, (r - l) * h);
            if (height[l] < height[r])
                l++;
            else
                r--;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> h(n);
    for (int &x : h)
        cin >> x;
    cout << Solution().maxArea(h) << '\n';
    return 0;
}
