#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int rob(vector<int>& nums) {
        int a = 0, b = 0;
        for (int x : nums) { int c = max(b, a + x); a = b; b = c; }
        return b;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    cout << Solution().rob(a) << '\n';
    return 0;
}
