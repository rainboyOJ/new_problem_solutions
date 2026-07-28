/**
 * Author by Rainboy
 */
// main.cpp：前缀和 + 哈希表统计前缀出现次数，O(n)。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        cnt[0] = 1;
        int sum = 0, ans = 0;
        for (int x : nums) {
            sum += x;
            auto it = cnt.find(sum - k);
            if (it != cnt.end()) ans += it->second;
            cnt[sum]++;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    cout << Solution().subarraySum(a, k) << '\n';
    return 0;
}
