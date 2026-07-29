/**
 * Author by Rainboy
 */
// main.cpp：按左端点排序，遍历合并 O(n log n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        for (auto &v : intervals) {
            if (ans.empty() || v[0] > ans.back()[1])
                ans.push_back(v);
            else
                ans.back()[1] = max(ans.back()[1], v[1]);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(2));
    for (int i = 0; i < n; i++)
        cin >> a[i][0] >> a[i][1];
    auto ans = Solution().merge(a);
    for (auto &v : ans)
        cout << v[0] << ' ' << v[1] << '\n';
    return 0;
}
