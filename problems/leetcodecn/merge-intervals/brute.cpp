/**
 * Author by Rainboy
 */
// brute.cpp：反复合并直到稳定 O(n²)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        bool changed = true;
        while (changed) {
            changed = false;
            vector<vector<int>> next;
            for (size_t i = 0; i < intervals.size(); i++) {
                bool merged = false;
                for (auto &cur : next) {
                    if (intervals[i][0] <= cur[1] && intervals[i][1] >= cur[0]) {
                        cur[0] = min(cur[0], intervals[i][0]);
                        cur[1] = max(cur[1], intervals[i][1]);
                        merged = true;
                        changed = true;
                        break;
                    }
                }
                if (!merged)
                    next.push_back(intervals[i]);
            }
            intervals = next;
        }
        return intervals;
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
