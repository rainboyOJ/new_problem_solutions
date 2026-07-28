/**
 * Author by Rainboy
 */
// brute.cpp：每次右移一位，重复 k 次 O(nk)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        for (int i = 0; i < k; i++) {
            int last = nums[n - 1];
            for (int j = n - 1; j > 0; j--)
                nums[j] = nums[j - 1];
            nums[0] = last;
        }
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    Solution().rotate(a, k);
    for (int x : a) cout << x << ' ';
    return 0;
}
