#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canJump(vector<int> &nums) {
        int reach = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            if (i > reach)
                return false;
            reach = max(reach, i + nums[i]);
        }
        return true;
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
    cout << Solution().canJump(a) << '\n';
    return 0;
}
