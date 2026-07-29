#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int> &nums) {
        int cand = 0, cnt = 0;
        for (int x : nums) {
            if (cnt == 0)
                cand = x;
            cnt += (x == cand) ? 1 : -1;
        }
        return cand;
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
    cout << Solution().majorityElement(a) << '\n';
    return 0;
}
