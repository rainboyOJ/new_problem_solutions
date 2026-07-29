#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int> &nums) {
        int prevTwo = 0, prevOne = 0;
        for (int value : nums) {
            int current = max(prevOne, prevTwo + value);
            prevTwo = prevOne;
            prevOne = current;
        }
        return prevOne;
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
    cout << Solution().rob(a) << '\n';
    return 0;
}
