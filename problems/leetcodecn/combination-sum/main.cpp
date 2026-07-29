#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> ans;
        vector<int> cur;
        function<void(int, int)> dfs = [&](int i, int left) {
            if (left == 0) {
                ans.push_back(cur);
                return;
            }
            if (i == (int)candidates.size() || left < 0)
                return;
            dfs(i + 1, left);
            cur.push_back(candidates[i]);
            dfs(i, left - candidates[i]);
            cur.pop_back();
        };
        dfs(0, target);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    for (auto &v : Solution().combinationSum(a, t)) {
        for (int x : v)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
