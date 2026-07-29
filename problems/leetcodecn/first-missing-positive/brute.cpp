/**
 * Author by Rainboy
 */
// brute.cpp：排序后扫描找第一个缺失的正数，O(n log n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int cur = 1;
        for (int x : nums) {
            if (x == cur)
                cur++;
        }
        return cur;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    cout << Solution().firstMissingPositive(a) << '\n';
    return 0;
}
