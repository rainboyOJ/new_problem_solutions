/**
 * Author by Rainboy
 */
// main.cpp：双指针维护左右最高柱，较矮侧水量可立即确定，O(n) O(1)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& h) {
        int l = 0, r = h.size() - 1, lmax = 0, rmax = 0, ans = 0;
        while (l < r) {
            if (h[l] < h[r]) {
                h[l] >= lmax ? lmax = h[l] : ans += lmax - h[l];
                l++;
            } else {
                h[r] >= rmax ? rmax = h[r] : ans += rmax - h[r];
                r--;
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    cout << Solution().trap(h) << '\n';
    return 0;
}
