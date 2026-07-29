/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 */
// main.cpp：双指针，write 指针收集非零元素，剩余补零。
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        int w = 0;
        for (int i = 0; i < (int)nums.size(); i++)
            if (nums[i])
                nums[w++] = nums[i];
        while (w < (int)nums.size())
            nums[w++] = 0;
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
    Solution().moveZeroes(a);
    for (int x : a)
        cout << x << ' ';
    return 0;
}
