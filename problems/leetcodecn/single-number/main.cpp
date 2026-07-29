#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int> &nums) {
        int ans = 0;
        for (int x : nums)
            ans ^= x;
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
    cout << Solution().singleNumber(a) << '\n';
    return 0;
}
