#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[j] += dp[j-1];
        return dp[n-1];
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin >> m >> n; cout << Solution().uniquePaths(m,n) << '\n';
    return 0;
}
