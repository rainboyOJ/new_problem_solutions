#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> cnt;
        for (int x : nums) cnt[x]++;
        vector<pair<int,int>> v(cnt.begin(), cnt.end());
        sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.second > b.second; });
        vector<int> ans(k);
        for (int i = 0; i < k; i++) ans[i] = v[i].first;
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k; vector<int> a(n); for (int& x : a) cin >> x;
    for (int x : Solution().topKFrequent(a, k)) cout << x << ' ';
    return 0;
}
