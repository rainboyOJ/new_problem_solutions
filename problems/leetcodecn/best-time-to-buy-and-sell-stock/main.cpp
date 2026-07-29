#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int mn = INT_MAX, ans = 0;
        for (int x : prices) {
            mn = min(mn, x);
            ans = max(ans, x - mn);
        }
        return ans;
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
    cout << Solution().maxProfit(a) << '\n';
    return 0;
}
