/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 */
// brute.cpp：枚举所有 (i,j) 对，O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size(), ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                ans = max(ans, (j - i) * min(height[i], height[j]));
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> h(n);
    for (int& x : h) cin >> x;
    cout << Solution().maxArea(h) << '\n';
    return 0;
}
