#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    vector<vector<int>> generate(int n) {
        vector<vector<int>> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i].resize(i+1, 1);
            for (int j = 1; j < i; j++) ans[i][j] = ans[i-1][j-1] + ans[i-1][j];
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for (auto& v : Solution().generate(n)) { for (int x : v) cout << x << ' '; cout << '\n'; }
    return 0;
}
