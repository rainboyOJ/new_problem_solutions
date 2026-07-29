/**
 * Author by Rainboy
 */
// brute.cpp：每个位置找左右最大高度，O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int> &h) {
        int n = h.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            int l = 0, r = 0;
            for (int j = i; j >= 0; j--)
                l = max(l, h[j]);
            for (int j = i; j < n; j++)
                r = max(r, h[j]);
            ans += min(l, r) - h[i];
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
    cout << Solution().trap(h) << '\n';
    return 0;
}
